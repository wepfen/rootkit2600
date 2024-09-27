# rootkit2600

## Introduction

Le but du projet est de réaliser un rootkit en C ainsi qu'un programme compagnon pour interagir avec.

Le rootkit embarquera des mécanismes :
- discretion, pour notamment masquer les fichiers qui le concerne ou les resultats de commande qui pourraient réveler ce dernier
- persistance
- et permettre des fonctionnalités malveillantes comme renvoyer un root shell


## Contexte

Après etre devenu root, on insère le rootkit en .ko dans la machine.

Ainsi, un utlisateur (dont on fournira les identifiants) pourra intéragir avec le rootkit grace à un programme compagnon.

Pour le contexte, la machine accepte les modules non signés.
