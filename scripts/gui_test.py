import asyncio
import os
import sys
from bleak import BleakScanner, BleakClient

# Detetar sistema operativo para leitura de teclado sem bloqueio
if os.name == 'nt':
    import msvcrt
else:
    import termios
    import tty
    import select

MAC_ADDRESS = "20:D1:01:79:78:0B"
UART_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"

# Estado atual do robô
robot_state = {
    "status": "STOPPED",
    "speed": 0.00,
    "battery": 0
}

rx_buffer = ""

def render_menu():
    # Limpa o ecrã e coloca o cursor no topo (ANSI)
    print("\033[2J\033[H", end="")
    print("==================MENU=====================")
    print(f"          STATUS     : {robot_state['status']}")
    print("          PRESS \"1\" TO START")
    print("          PRESS \"2\" TO STOP")
    print(f"          BASE SPEED : {robot_state['speed']:.2f}  (+ / -)")
    print(f"          BATTERY    : {robot_state['battery']}%")
    print("          PRESS \"q\" TO QUIT")
    print("===========================================", flush=True)

def notification_handler(sender, data):
    global rx_buffer
    rx_buffer += data.decode('utf-8', errors='ignore')

    # Processa apenas quando chega o '\n' (evita erros de pacotes partidos)
    while '\n' in rx_buffer:
        line, rx_buffer = rx_buffer.split('\n', 1)
        line = line.strip()
        if not line:
            continue

        parts = line.split(',')
        if len(parts) == 3:
            try:
                robot_state["status"] = "RUNNING" if int(parts[0]) == 1 else "STOPPED"
                robot_state["speed"] = float(parts[1])
                robot_state["battery"] = int(parts[2])
                render_menu()
            except ValueError:
                pass # Ignora pacotes corrompidos

def get_key_non_blocking():
    if os.name == 'nt':
        if msvcrt.kbhit():
            return msvcrt.getch().decode('utf-8', errors='ignore')
        return None
    else:
        dr, _, _ = select.select([sys.stdin], [], [], 0)
        if dr:
            return sys.stdin.read(1)
        return None

async def main():
    # Ativa suporte a códigos ANSI no terminal do Windows
    if os.name == 'nt':
        os.system("")

    print(f"Scanning for JDY-23 ({MAC_ADDRESS})...")
    device = await BleakScanner.find_device_by_address(MAC_ADDRESS, timeout=10.0)

    if not device:
        print("Device not found.")
        return

    print(f"Device found: {device.name}. Connecting...")

    async with BleakClient(device) as client:
        await client.start_notify(UART_UUID, notification_handler)
        render_menu()

        # Configura terminal em modo raw no Linux/macOS
        old_settings = None
        if os.name != 'nt':
            old_settings = termios.tcgetattr(sys.stdin)
            tty.setcbreak(sys.stdin.fileno())

        try:
            while True:
                key = get_key_non_blocking()
                if key:
                    if key.lower() == 'q':
                        break
                    if key in ('1', '2', '+', '-'):
                        # response=False é mais rápido e evita bloqueios no JDY-23
                        await client.write_gatt_char(UART_UUID, key.encode('utf-8'), response=False)

                await asyncio.sleep(0.05) # Poll do teclado a cada 50ms
        finally:
            if os.name != 'nt' and old_settings:
                termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_settings)
            await client.stop_notify(UART_UUID)
            print("\nDisconnected.")

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\nExiting...")
