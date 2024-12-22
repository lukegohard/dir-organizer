import os
import random
import platform
import shutil  # Importa shutil per usare rmtree

# Funzione per pulire la console
def clear_console():
    system = platform.system().lower()
    if system == 'windows':
        os.system('cls')  # Per Windows
    else:
        os.system('clear')  # Per Unix-like (Linux/Mac)

# Colori ANSI
GREEN = '\033[32m'  # Verde
YELLOW = '\033[33m'  # Giallo
RESET = '\033[39m'  # Reset per il colore

# Lista di estensioni aggiornate, organizzate per categoria
extensions = [
    # Documenti
    'txt', 'doc', 'docx', 'pdf', 'rtf', 'odt', 'xls', 'xlsx', 'ppt', 'pptx',
    # Immagini
    'jpg', 'jpeg', 'png', 'gif', 'bmp', 'tiff', 'svg', 'ico',
    # Video
    'mp4', 'mkv', 'avi', 'mov', 'wmv', 'flv',
    # Audio
    'mp3', 'wav', 'flac', 'aac', 'ogg', 'm4a',
    # Archivio
    'zip', 'rar', '7z', 'tar', 'gz', 'iso',
    # Dati
    'csv', 'json', 'xml', 'sql',
    # Programmazione
    'c', 'cpp', 'h', 'java', 'py', 'js', 'html', 'css', 'php',
    # Eseguibili
    'exe', 'bat', 'sh', 'msi', 'apk', 'jar',
    # Configurazione e log
    'ini', 'log'
]

# Pulire la console all'avvio
clear_console()

# Input per il range
rng = int(input(f"{YELLOW}Enter range => {RESET}"))

# Input per la modalità di creazione
print(f"{YELLOW}Choose creation mode:")
print(f"{YELLOW}1. Only files")
print(f"{YELLOW}2. Files and folders (with subfolders){RESET}")
mode = int(input(f"{YELLOW}Enter choice (1/2) => {RESET}"))

# Directory base
base_dir = 'sample_data'

# Se la cartella esiste già, eliminarla e poi ricrearla
if os.path.exists(base_dir):
    shutil.rmtree(base_dir)  # Rimuove la cartella e il suo contenuto
os.makedirs(base_dir, exist_ok=True)

# Creazione in base alla scelta dell'utente
for i in range(rng):
    if mode == 1:  # Solo file
        # Creazione di un file casuale
        ext = random.choice(extensions)
        file_name = f'file_{i}.{ext}'
        file_path = os.path.join(base_dir, file_name)

        with open(file_path, 'w') as f:
            f.write('Sample content')

    elif mode == 2:  # Entrambi file e cartelle
        if random.random() < 0.2:  # 20% di probabilità di creare una cartella
            folder_name = f'folder_{i}'
            folder_path = os.path.join(base_dir, folder_name)
            os.makedirs(folder_path, exist_ok=True)

            # 30% di probabilità di creare una sottocartella
            if random.random() < 0.3:
                subfolder_name = f'subfolder_{i}'
                subfolder_path = os.path.join(folder_path, subfolder_name)
                os.makedirs(subfolder_path, exist_ok=True)
        else:  # Creazione di un file
            ext = random.choice(extensions)
            file_name = f'file_{i}.{ext}'

            # Decidi casualmente se mettere il file in una sottocartella
            if random.random() < 0.3:  # 30% di probabilità di mettere in una sottocartella
                subfolders = [f.path for f in os.scandir(base_dir) if f.is_dir()]
                if subfolders:
                    folder_path = random.choice(subfolders)
                    file_path = os.path.join(folder_path, file_name)
                else:
                    file_path = os.path.join(base_dir, file_name)
            else:
                file_path = os.path.join(base_dir, file_name)

            with open(file_path, 'w') as f:
                f.write('Sample content')

print(f"{GREEN}[+] File and folder creation completed.{RESET}")