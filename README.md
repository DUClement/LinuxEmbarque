Clément DU
Laksan THIRUKUMARAN

# TP1 - Prise en main
## Connexion au système
Une fois connecté au SoC et après avoir tapé ces commandes suivantes : 
```
./expand_rootfs.sh
./resize2fs_once
```
Nous passons d'un espace de 3 GO à 15 GO disponibles.
## Exploration des dossiers /sys/class et /proc
- /sys/class/leds/fpga_ledX/ donne accès aux contrôles des LED de la FPGA
— /proc/ioport fournit des informations sur les adresses entrées/sorties des péripéhriques
— /proc/iomem contient les informations des adresses mémoires
— /proc/device-tree/sopc@0
## Compilation croisée
La commande suivante permet de faire de la cross-compilation :
```
arm-linux-gnueabihf-gcc hello.c -o hello.o
```
./hello.c ne s'exécute pas car il s'agit d'un fichier binaire que la VM ne peut pas exécuter, il faut passer par la carte VEEK.
## Accès au matériel (echo) et chenillard
```
echo "1" > /sys/class/leds/fpga_led1/brightness
```


# TP2 - Prise en main
