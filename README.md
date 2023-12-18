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

Cette commande,```arm-linux-gnueabihf-gcc hello.c -o hello.o```, permet de faire de la cross-compilation.

./hello.c ne s'exécute pas car il s'agit d'un fichier binaire que la VM ne peut pas exécuter, il faut passer par la carte VEEK.
## Accès au matériel (echo) et chenillard

```echo "1" > /sys/class/leds/fpga_led1/brightness``` allume la led à la position 1 simplement

Nous allons mettre en place un chenillard en s'inspirant de la ligne de commande d'au dessus.
*cf* _TP1_/_chenillard.c_ et son exécutable.
_cf_ **TP1**/**chenillard.c**
Nous ouvrons les fichiers ```/sys/class/leds/fpga_ledx/brightness``` où ```x``` représente le numéro de led et est remplacé puis nous écrivons dans la valeur de la led afin de l'allumer et l'éteindre.

# TP2 - Modules kernel
## Accès aux registres
*cf* _TP2_/_mmap_/_mmap.c_
## Compilation de module noyau sur la VM
Les programmes suivants :
— utilisation de paramètres au chargement du module
— création d’un entrée dans /proc
— utilisation d’un timer
sont assemblés en un seul programme *cf* _TP2_/_proc_/_proc.c_ par conséquent son programme est *cf* _TP2_/_proc_/_proc.ko_
```
export CROSS_COMPILE=<chemin_arm-linux-gnueabihf->
export ARCH=arm
make prepare
make scripts
```
```export``` permet de définir des variables d'environnement qui peuvent être utilisées par les processus en cours d'exécution
