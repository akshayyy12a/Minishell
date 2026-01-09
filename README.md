# Minishell 🐚

Minishell est un projet du cursus a faire en duo de l’école 42 dont l’objectif est de recréer un **shell Unix simplifié**, inspiré de bash.  
Ce projet met l’accent sur la compréhension approfondie des processus, de la gestion mémoire, des signaux et de l’interaction avec le système d’exploitation.

---

## 🎯 Objectifs du projet

- Comprendre le fonctionnement interne d’un shell
- Manipuler les **processus** (fork, exec, wait)
- Gérer les **signaux Unix** (Ctrl-C, Ctrl-D, Ctrl-\)
- Implémenter un **parser** robuste
- Approfondir la gestion de la mémoire en C

---

## ⚙️ Fonctionnalités

### Commandes
- Exécution de commandes absolues et relatives
- Recherche dans le `PATH`

### Builtins implémentés
- `echo` (avec option `-n`)
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### Redirections
- `<` redirection d’entrée
- `>` redirection de sortie
- `>>` redirection en mode append
- `<<` heredoc

### Pipes
- Gestion des pipes (`|`) entre plusieurs commandes

### Variables d’environnement
- Expansion des variables (`$VAR`)
- Gestion de `$?` (code de retour)

### Signaux
- Comportement similaire à bash pour :
  - `Ctrl-C`
  - `Ctrl-D`
  - `Ctrl-\`

---

## 🛠️ Technologies utilisées

- **Langage** : C
- **Norme** : Norme 42
- **Bibliothèques système** :
  - `readline`
  - `unistd`
  - `signal`
  - `fcntl`
  - `sys/wait`

---

## 🚀 Installation et lancement

```bash
git clone https://github.com/akshayyy12a/Minishell.git
cd Minishell
make
./minishell
```

Realisé avec Senhayl, étudiant a 42.
