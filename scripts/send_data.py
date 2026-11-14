import asyncio
from bleak import BleakScanner, BleakClient
from prompt_toolkit import PromptSession
from prompt_toolkit.patch_stdout import patch_stdout

MAC_ADDRESS = "20:D1:01:79:78:0B"
UART_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"

def notification_handler(sender, data):
    # O .strip() remove quebras de linha extra para o print ficar limpo
    print(f"[Robo]: {data.decode('utf-8', errors='ignore').strip()}")

async def main():
    print(f"A procurar {MAC_ADDRESS}...")
    device = await BleakScanner.find_device_by_address(MAC_ADDRESS, timeout=10.0)

    if not device:
        print("Dispositivo não encontrado.")
        return

    async with BleakClient(device) as client:
        print("Ligado!")
        await client.start_notify(UART_UUID, notification_handler)
        
        # Cria a sessão de prompt assíncrona
        session = PromptSession()
        
        while True:
            # O patch_stdout redireciona os prints do notification_handler 
            # para cima da barra de input de forma limpa
            with patch_stdout():
                comando = await session.prompt_async("Enviar: ")
            
            if comando:
                comando_final = comando + "\n"
                await client.write_gatt_char(UART_UUID, comando_final.encode('utf-8'), response=False)

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\nSaída.")
