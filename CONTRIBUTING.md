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

Pour l'implémentation du module kernel il suffit de se baser sur l'architecture définie (Voir [Architecture LKM](README.md#lkm)).

Pour ajouter une fonctionnalité il vous suffit de créer un fichier `.c` et `.h` dans le dossier `src/rootkit/` et `src/rootkit/include/` respectivement.

```diff
  src/rootkit/
  ├── core.c
+ ├── my_feature.c
  ├── include
  │   ├── config.h
+ │   ├── my_feature.h
  │   ├── core.h
  │   └── debug.h
  ├── init.c
  └── makefile
```

Pour que votre fonctionalité soit appellée par le module il vous faudra inclure le fichier `.h` dans le fichier `core.c`. Puis appeler la fonctionnalité dans le `core_start` ou `core_stop`.

```diff
  #include "core.h"

+ #include "my_feature.h"

  int core_start(void) {
    DEBUG("core_start\n");

+   my_feature();

    return 0;
  }

  void core_stop(void) {
    DEBUG("core_stop\n");

+   my_feature_other_function();

      return;
  }
```

Si vous souhaiter compiler le module avec votre fonctionnalité il vous faudra inclure l'objet dans le `makefile`.

```diff
  # Module
  obj-m := $(ROOTKIT).o

  # Core
  $(ROOTKIT)-y += core.o init.o

  # Fonctionnalities
+ #$(ROOTKIT)-y += my_feature.o
```

#### C2

A définir.

### Commentaires

Pour que tout le monde puisse bien comprendre le code de tout un chacun il est impératif de commenter son code. Les commentaires doivent être concis et explicites.

Il existe une variété de tag pour aider à la compréhension du code.

| Tag | Description |
| --- | ----------- |
| @file | Description du fichier |
| @author | Auteur du fichier |
| @brief | Description brève |
| @param | Description d'un paramètre |
| @return | Description du retour |
| @example | Exemple d'utilisation |
| @note | Note |
| @struct | Description d'une structure |
| @enum | Description d'une énumération |
| @var | Description d'une variable |
| @def | Description d'une macro |
| @todo | Tâche à faire |
| @see | Lien vers une ressource ou code |

#### Fichiers

Les fichiers sources doivent commencer par un commentaire décrivant le fichier.

```c
/**
 * @file my_feature.c
 * @author [Optional]
 * 
 * @brief Implementation for my feature
 * 
 * Description of the file content
 */
```

#### Structures

Les structures doivent être commentées pour expliquer leur utilité.

```c
/**
 * @brief My Super Structure
 * @struct my_struct
 * 
 * Description of the structure
 * 
 * @var int my_var Description of the variable
 * @var char *my_string Description of the variable
 * @var void *my_pointer Description of the variable
 */
struct my_struct {
  int my_var;
  char *my_string;
  void *my_pointer;
};
```

#### Enumérations

Les énumérations doivent être commentées pour expliquer leur utilité.

```c
/**
 * @brief My Super Enum
 * @enum my_enum
 * 
 * Description of the enumeration
 * 
 * @var MY_ENUM_VALUE Description of the value
 * @var MY_ENUM_VALUE2 Description of the value
 */
enum my_enum {
  MY_ENUM_VALUE,
  MY_ENUM_VALUE2
};
```

#### Fonctions

Les fonctions doivent être commentées pour expliquer leur utilité.

```c
/**
 * @brief Description de la fonction
 * 
 * @param arg1 Description du paramètre
 * @param arg2 Description du paramètre
 * @return int Description du retour
 */
int my_function(int arg1, int arg2) {
  return arg1 + arg2;
}
```

On peut rajouter des examples, des notes ainsi que des références dans le corps du commentaire d'une fonction pour expliquer son fonctionnement.

```c
/**
 * @brief Description de la fonction
 * 
 * @param arg1 Description du paramètre
 * @param arg2 Description du paramètre
 * @return int Description du retour
 * 
 * @example
 * my_function(1, 2) // 3
 * 
 * @note Note sur la fonction
 * 
 * @see my_other_function
 * @see my_other_function2
 */
int my_function(int arg1, int arg2) {
  return arg1 + arg2;
}
```

### Nommage

Nous allons nommer nos variables, fonctions, structures, énumérations, etc, ... en anglais. Il est important de respecter une certaine cohérence dans le nommage pour que tout le monde puisse comprendre le code.

Chaque nom doit être explicite sur son utilité et ne doit pas contenir de surplus d'abréviation.

#### Variables

Les variables devront respecter plusieurs règles de nommage en plus de la convention de nommage [Snake Case](https://en.wikipedia.org/wiki/Snake_case).

- Les variables globales devront commencer par `g_`.
- Les variables statiques devront commencer par `s_`.
- Les variables locales n'ont pas de préfixe.
- Les pointeurs devront commencer par `p_`.

```c
int g_my_global_variable;
static int s_my_static_variable;

void my_function(void) {
  int my_local_variable;
  int *p_my_pointer;
}
```

#### Macros et Constantes

Les macros et les constantes devront toujours être en majuscules et séparées par des `_`.

```c
#define MY_MACRO 42
const int MY_CONSTANT = 42;
```

#### Fonctions

Les fonctions ne devront pas contenir de préfixe et devront respecter la convention de nommage [Snake Case](https://en.wikipedia.org/wiki/Snake_case).

> Note : Une fonction ne doit pas dépasser les 100 lignes de code. (Et encore c'est beaucoup mdrrr)

```c
void my_function(void) {
  return;
}
```

#### Structures et Enumérations

Pour le nom des structures et des énumérations nous allons cette fois-ci respecter le nommage en [Pascale Case](https://en.wikipedia.org/wiki/Pascale_case).

C'est à dire qu'un nom devra être sufixé par `_t`.

```c
typedef struct my_structure_t {
  int my_var;
} my_structure_t;

typedef enum my_enum_t {
  MY_ENUM_VALUE,
  MY_ENUM_VALUE2
} my_enum_t;
```
