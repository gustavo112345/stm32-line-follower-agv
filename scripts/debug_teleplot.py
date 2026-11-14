import asyncio
import socket
from bleak import BleakScanner, BleakClient

MAC_ADDRESS = "20:D1:01:79:78:0B"
UART_TX_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"

# Configuração do socket UDP para o Teleplot Web
UDP_IP = "teleplot.fr"
UDP_PORT = 46172
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

data_buffer = ""

def notification_handler(sender, data):
    global data_buffer
    
    # Acumula os bytes convertidos para string
    data_buffer += data.decode('utf-8', errors='ignore')
    
    # Se houver uma quebra de linha, significa que temos dados completos
    if '\n' in data_buffer:
        linhas = data_buffer.split('\n')
        
        # Envia apenas as linhas completas
        for linha in linhas[:-1]:
            linha_limpa = linha.strip()
            if linha_limpa:
                # Envia por UDP a linha formatada com \n no fim para o parser do Teleplot
                sock.sendto((linha_limpa + '\n').encode('utf-8'), (UDP_IP, UDP_PORT))
                # Imprime no terminal para verificação visual
                print(linha_limpa, flush=True)
                
        # Guarda o fragmento restante no buffer
        data_buffer = linhas[-1]

async def main():
    print(f"A procurar JDY-23 ({MAC_ADDRESS})...")
    device = await BleakScanner.find_device_by_address(MAC_ADDRESS, timeout=10.0)
    
    if not device:
        print("Módulo não encontrado. Verifica se não está emparelhado com nada (LED a piscar).")
        return

    print(f"Módulo encontrado ({device.name})! A iniciar ponte BLE -> UDP ({UDP_IP}:{UDP_PORT})...")
    
    async with BleakClient(device) as client:
        print("Ligação estabelecida! À escuta de dados (Ctrl+C para sair)...")
        await client.start_notify(UART_TX_UUID, notification_handler)
        
        while True:
            await asyncio.sleep(1)

if __name__ == "__main__":
    asyncio.run(main())
