# LKM Rootkit 2600 (6.X)

Rootkit linux pour les version kernel __6.X__

> ⚠️⚠️⚠️
>
> Ce projet existe dans un but éducatif uniquement nous ne sommes pas responsable de vos agissements ni des conséquences en cas d'utilisation malveillante de ce rootkit.
>
> ⚠️⚠️⚠️

## Introduction

Le but de ce projet est de réaliser un rootkit linux ainsi qu'un C2 (Command Controller) permettant de communiquer avec le module kernel.

## Objectifs

Les objectifs de ce rootkit sont les suivants :

- La discrétion (module kernel caché, pas de logs, fichiers cachés, processus cachés, ...)
- La persistence (module kernel persistant après un reboot)
- Fonctionalités malveillante (shell root, keylogger, backdoor, ...)
- Un C2 pour communiquer avec le module kernel (commandes, logs, ...)

Les différentes fonctionalités ainsi que son fonctionnement seront plus détaillées dans la partie [Architecture](#architecture).

## Contexte

Après etre devenu root, on injecte le module kernel en `.ko` dans la machine.

Ainsi, un utlisateur (dont on fournira les identifiants) pourra intéragir avec le rootkit grace à un programme compagnon (C2) qui permettra de communiquer avec le module kernel.

Pour le contexte, la machine accepte les modules non signés.

## Installation

Ce rootkit n'étant qu'un simple module kernel linux, il suffit de le compiler puis de le charger dans son kernel.

> Note : Je vous recommande de tester le rootkit sur une VM (via un shared folder) de façon à ne pas abimer votre propre OS/Kernel.

### Prérequis

Avant de tester votre rootkit il vous faudra les sources d'un kernel linux (6.X) pour compiler votre module. Pour se faire vous pouvez utiliser le script `get_kernel.sh` qui vous permettra de télécharger les sources du kernel.

```bash
./scripts/get_kernel.sh <version_kernel> # Exemple : ./scripts/get_kernel.sh 6.11
```

> Note : Vous pouvez aussi télécharger les sources du kernel via le site officiel de [kernel.org](https://www.kernel.org/).

Il vous faudra ensuite compiler votre kernel une première fois.

```bash
./scripts/compile_kernel.sh <version_kernel> # Exemple : ./scripts/compile_kernel.sh 6.11
```

> Note : Si vous souhaitez compiler votre kernel avec une configuration spécifique vous pouvez le faire via la commande `make menuconfig` dans le dossier de vos sources.

Maintenant que votre kernel est compilé il faut créer une image disque configurée avec votre kernel et la monter.

> *TODO* : Ajouter le script pour créer une image disque LFS. Voir [LFS](#lfs).

Pour se faire vous devez utiliser le script `to_be_defined.sh` qui vous permettra de créer une image disque et de la monter.

```bash
./scripts/to_be_defined.sh
```

### Build

Pour compiler votre module basé sur votre version kernel.

```bash
make
```

Normalement cette commande doit se finir en créant plusieurs fichiers dont un `.ko`. Celui que nous allons charger dans notre kernel.

### Load

Une fois le module compiler et que votre fichier `.ko` est bien visible vous pouvez le charger via la commande suivante

```bash
make install
```

### Unload

Pour décharger votre module de votre kernel actuel.

```bash
make remove
```

### Logs

Si vous souhaitez voir les logs générés par votre module.

```bash
dmesg
dmesg | tail # Pour n'afficher que la fin des logs
dmesg | grep <> # Pour n'afficher que certaines lignes correspondantes à une recherche
```

### Clean

Pour nettoyer votre environnement de développement.

```bash
make clean
```

## Développement et Contribution

Pour le développement du projet merci de vous référer à la page [Comment contribuer au projet](CONTRIBUTING.md).

## Architecture

Ce rootkit se découpe en deux parties bien distincte un LKM (Linux Kernel Module) et un C2 (Command Controller) permettant de s'interfacer avec votre module kernel.

### LKM

### C2

> *TODO* : Expliquer les tenants et aboutissants du C2 permettant de communiquer avec le module kernel.
>
> - Définir la stack utilisée (Python, C)
> - Définir le mode de communication (Local via device, Local via socket, Local via syscall, Remote via socket, ...)
> - Définir les commandes disponibles (shell, keylogger, backdoor, ...)
>

## LFS

> *TODO* : Expliquer les tenants et aboutissants du script permettant de créer une image disque LFS.

### Ressources

- [Rootkit Tutorial using Vagrant](https://xcellerator.github.io/posts/linux_rootkits_01/)
- [Awesome Linux Rootkits](https://github.com/milabs/awesome-linux-rootkits)
- [Creating a Rootkit to Learn C](https://h0mbre.github.io/Learn-C-By-Creating-A-Rootkit/)
- [kprochide](https://github.com/spiderpig1297/kprochide)
