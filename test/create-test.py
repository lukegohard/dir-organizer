import os
import random

extensions = ['txt', 'jpg', 'pdf', 'docx', 'png', 'csv', 'mp3', 'mp4']
rng = int(input("Enter range => "))
base_dir = 'sample_data'

os.makedirs(base_dir, exist_ok=True)

for i in range(rng):
    # Decidi casualmente se creare un file o una cartella
    if random.random() < 0.2:  # 20% di probabilità di creare una cartella
        folder_name = f'folder_{i}'
        folder_path = os.path.join(base_dir, folder_name)
        os.makedirs(folder_path, exist_ok=True)
    else:
        # Crea un file, possibilmente in una sottocartella casuale
        ext = random.choice(extensions)
        file_name = f'file_{i}.{ext}'
        
        # Decidi casualmente se mettere il file in una cartella
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