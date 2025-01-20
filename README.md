# Minishell

Un shell minimaliste, aussi mignon qu’un vrai shell ! 🚀

## Description

**Minishell** est un projet réalisé dans le cadre du cursus 42. Son objectif est de créer un shell minimaliste permettant de comprendre les mécanismes de base des processus, des descripteurs de fichiers, et de la gestion des commandes en ligne.

Ce projet vise à répliquer certaines fonctionnalités de Bash tout en respectant les contraintes d’un environnement strict.

## Fonctionnalités

- Affichage d'un prompt interactif en attente de commande.
- Gestion d'un historique des commandes.
- Exécution des commandes via la recherche du bon exécutable :
  - Basée sur la variable `PATH`.
  - Chemins relatifs ou absolus.
- Gestion des redirections :
  - `<` : redirection de l’entrée.
  - `>` : redirection de la sortie.
  - `<<` : délimiteur pour lire l’input jusqu’à une ligne contenant le délimiteur.
  - `>>` : redirection de la sortie en mode append.
- Gestion des pipes (`|`) pour connecter plusieurs commandes.
- Substitution des variables d'environnement (`$variable`).
- Support de la variable spéciale `$?` pour le statut de sortie de la dernière commande.
- Gestion des caractères spéciaux :
  - Quotes simples `'` et doubles `"` (avec gestion partielle des métacaractères).
- Implémentation des builtins :
  - `echo` (avec l’option `-n`).
  - `cd` (avec un chemin relatif ou absolu).
  - `pwd`, `export`, `unset`, `env`, `exit` (sans options).

### Gestion des signaux
- **Ctrl-C** : Affiche un nouveau prompt.
- **Ctrl-D** : Quitte le shell.
- **Ctrl-\\** : Ne fait rien.

## Compilation

Pour compiler le projet, utilisez le `Makefile` fourni :
```bash
make
```

Cela génère un exécutable nommé minishell.

### Commandes Makefile :
```bash
make all : Compile le projet.
make clean : Supprime les fichiers objets.
make fclean : Supprime les fichiers objets et l`exécutable.
make re : Re-compile tout le projet.
```

## Utilisation :
### Lancez le shell avec :
```bash
./minishell
```

### Exemples :

```bash
minishell$ echo "Hello, world!"
Hello, world!

minishell$ ls | grep minishell > output.txt
```


### Contraintes techniques.
- Une seule variable globale autorisée.
- Respect strict de la norme 42.
- Pas de fuites mémoire autorisées (excepté celles de la fonction readline).
- Compatible avec les bibliothèques suivantes : readline, printf, malloc, etc.

### Auteur

Ce projet a été développé par ***kscarmy***.

### Notes :

- Les bonus mentionnés dans le sujet (e.g., &&, ||, *) n'ont pas été implémentés.
- Pour toute question ou suggestion, ouvrez une issue sur le dépôt GitHub.

