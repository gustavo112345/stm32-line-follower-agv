import asyncio
from bleak import BleakScanner, BleakClient

MAC_ADDRESS = "20:D1:01:79:78:0B"
UART_TX_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"

def notification_handler(sender, data):
    # Decode incoming bytes to string and print directly to the terminal
    print(data.decode('utf-8', errors='ignore'), end="", flush=True)

async def main():
    print(f"Scanning for JDY-23 ({MAC_ADDRESS})...")

    # 1. Scan for the device physically to bypass OS cache issues
    device = await BleakScanner.find_device_by_address(MAC_ADDRESS, timeout=10.0)

    if not device:
        print("Device not found.")
        return

    print(f"Device found: {device.name} Connecting...")

    # 2. Pass the device object to the client to ensure proper GATT socket initialization
    async with BleakClient(device) as client:
        print("Connection established! Listening for incoming data (Press Ctrl+C to exit)...")

        await client.start_notify(UART_TX_UUID, notification_handler)

        # Keep the script running to receive continuous notifications
        while True:
            await asyncio.sleep(1)

if __name__ == "__main__":
    asyncio.run(main())
