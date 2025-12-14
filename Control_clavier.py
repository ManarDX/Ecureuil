import serial
import time
import keyboard

arduino = serial.Serial('COM5', 9600)
time.sleep(2)

while True: 
    if keyboard.is_pressed('up') or keyboard.is_pressed('c'): 
        cmd='c' 
    elif keyboard.is_pressed('down') or keyboard.is_pressed('d'): 
        cmd = 'd' 
    else: 
        cmd='s' 
    arduino.write(cmd.encode()) 
    time.sleep(0.05)


# import bluetooth

# # Nom de ton module HC-05
# hc05_name = "ECUREUIL"

# def find_hc05():
#     print("Recherche des périphériques Bluetooth...")
#     devices = bluetooth.discover_devices(duration=8, lookup_names=True)
#     for addr, name in devices:
#         if name == hc05_name:
#             print(f"HC-05 trouvé : {name} [{addr}]")
#             return addr
#     print("HC-05 introuvable.")
#     return None

# def connect_hc05(addr):
#     port = 1  # Le port RFCOMM standard pour HC-05
#     sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
#     print(f"Connexion à {addr} sur le port {port}...")
#     try:
#         sock.connect((addr, port))
#         print("Connecté !")
#         return sock
#     except bluetooth.btcommon.BluetoothError as err:
#         print(f"Erreur de connexion : {err}")
#         return None

# def main():
#     addr = find_hc05()
#     if not addr:
#         return

#     sock = connect_hc05(addr)
#     if not sock:
#         return

#     try:
#         while True:
#             # Envoyer une commande à l'HC-05
#             message = input("Message à envoyer (ou 'exit' pour quitter) : ")
#             if message.lower() == "exit":
#                 break
#             sock.send(message)

#             # Recevoir la réponse
#             data = sock.recv(1024)
#             if data:
#                 print(f"Réponse HC-05 : {data.decode('utf-8', errors='ignore')}")
#     except KeyboardInterrupt:
#         print("\nFermeture du script...")
#     finally:
#         sock.close()
#         print("Déconnecté.")

# if __name__ == "__main__":
#     main()
