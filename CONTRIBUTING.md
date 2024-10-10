# Comment contribuer au projet

Ce projet est réaliser dans le cadre d'un cours il n'y a donc que les membres du groupe qui peuvent y contribuer, toute autre contribution sera rejeté.

## Git

Nous utilisont Git comme outils collaboratif afin de regrouper notre travail dans un même endroit. Pour ne pas atteindre au bon déroulé du projet il est nécéssaire de sen tenir le plus possible au rêgles établis ci-dessous.

### Branches

Nous allons définir plusieurs branches dont une `main` et une `develop` il ne sera pas autorisé à pousser son code directement sur ces branches ci (mis à part via merge request).

Chaque personne pourra créer ca branche et poussera son code comme il le souhaite dessus. L'objectif ici est de pouvoir travailler tous ensemble sur différents sujets en même temps.

Avant de commencer à développer il vous faudra créer votre branche à l'aide des commandes suivantes :

```bash
git checkout -b <nom_de_la_branche>
```

Une fois votre travail terminé vous pourrez pousser votre code sur votre branche via la commande suivante :

```bash
git push origin <nom_de_la_branche>
```

### Commits

Les noms des commits doivent être concis et explicite. Ici pas d'obligations sur la forme du message de commit mais vous pouvez respecter la norme suivante pour plus de clarté [CommitLint](https://commitlint.io/).

Rappels des commandes pour commit :

```bash
git add <fichier> # Ajouter un fichier à l'index
git add . # Ajouter tous les fichiers à l'index
```

```bash
git commit -m "Message de commit" # Commiter les fichiers ajoutés à l'index
```

### Merge Request

Les merge request sont les seuls moyens de pousser son code sur les branches `main` et `develop`. Pour cela il vous faudra créer une merge request sur la page du projet (Github).

## Code

Le code rendu devra respecter les normes [ANSSI C](https://cyber.gouv.fr/sites/default/files/2020/07/anssi-guide-regles_de_programmation_pour_le_developpement_securise_de_logiciels_en_langage_c-v1.4.pdf) pour le module kernel et [PEP8](https://peps.python.org/pep-0008/) pour le C2. Il est donc impératif que chaque membresdu groupes veille un maximum sur le respect de ces normes (commentaire, nommage, etc, ...)

### Développement

#### LKM

#### C2

A définir.

### Commentaires

### Nommage