# Projet Philosophers

Ce dépôt contient la réalisation du projet Philosophers de l'école 42. Le projet consiste à implémenter le problème classique des philosophes mangeurs en utilisant les threads et la gestion des ressources partagées. Il comprend une partie obligatoire et une partie bonus, chacune avec ses propres exigences et implémentations.

## Table des matières

- [Aperçu](#aperçu)
- [Règles globales](#règles-globales)
- [Partie obligatoire](#partie-obligatoire)
- [Partie bonus](#partie-bonus)
- [Compilation et exécution](#compilation-et-exécution)

## Aperçu

### Contexte

- Un ou plusieurs philosophes s'assoient autour d'une table ronde avec un grand bol de spaghetti au milieu.
- Les philosophes alternent entre manger, penser et dormir.
- Lorsqu'ils mangent, ils ne pensent ni ne dorment; lorsqu'ils pensent, ils ne mangent ni ne dorment; et lorsqu'ils dorment, ils ne mangent ni ne pensent.
- Chaque philosophe prend les fourchettes à sa droite et à sa gauche pour manger.
- Après avoir mangé, ils reposent leurs fourchettes et commencent à dormir, puis à penser une fois réveillés. La simulation s'arrête lorsqu'un philosophe meurt de faim.
- Chaque philosophe doit manger pour éviter de mourir de faim.
- Les philosophes ne se parlent pas et ne savent pas si un autre philosophe est sur le point de mourir.

## Règles globales

- Les variables globales sont interdites.
- Les programmes doivent accepter les arguments suivants :
  - `number_of_philosophers`: Le nombre de philosophes et de fourchettes.
  - `time_to_die` (en millisecondes) : Temps avant qu'un philosophe meure s'il ne mange pas.
  - `time_to_eat` (en millisecondes) : Temps qu'un philosophe met pour manger.
  - `time_to_sleep` (en millisecondes) : Temps qu'un philosophe met pour dormir.
  - `number_of_times_each_philosopher_must_eat` (argument optionnel) : Nombre de fois que chaque philosophe doit manger avant que la simulation ne s'arrête.
- Chaque philosophe a un numéro allant de 1 à `number_of_philosophers`.
- Les logs de l'état des philosophes doivent être formatés de manière cohérente et ne doivent pas être mélangés avec d'autres messages.

## Partie obligatoire

- **Nom du programme** : `philo`
- **Dossier** : `philo/`
- **Fichiers à rendre** : Makefile, *.h, *.c
- **Fonctions externes autorisées** : `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`
- **Description** : Implémentation des philosophes avec des threads et des mutexes
- Chaque philosophe est un thread.
- Les fourchettes sont protégées par des mutex pour éviter les duplications.

## Partie bonus

- **Nom du programme** : `philo_bonus`
- **Dossier** : `philo_bonus/`
- **Fichiers à rendre** : Makefile, *.h, *.c
- **Fonctions externes autorisées** : `memset`, `printf`, `malloc`, `free`, `write`, `fork`, `kill`, `exit`, `pthread_create`, `pthread_detach`, `pthread_join`, `usleep`, `gettimeofday`, `waitpid`, `sem_open`, `sem_close`, `sem_post`, `sem_wait`, `sem_unlink`
- **Description** : Implémentation des philosophes avec des processus et des sémaphores
- Les fourchettes sont représentées par un sémaphore.
- Chaque philosophe est un processus, mais le processus principal ne doit pas être un philosophe.

## Compilation et exécution

### Partie Obligatoire

1. Accédez au dossier `philo` :
   ```
   cd philo
   ```

2. Compilez le projet :
   ```
   make
   ```

3. Exécutez le programme :
   ```
   ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
   ```
	Exemple :
   ```
   ./philo 4 500 200 200
   ./philo 10 800 300 300 7
   ```

### Partie Bonus

1. Accédez au dossier `philo_bonus` :
   ```
   cd philo_bonus
   ```

2. Compilez le projet :
   ```
   make
   ```

3. Exécutez le programme :
   ```
   ./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
   ```
	Exemple :
   ```
   ./philo_bonus 4 500 200 200
   ./philo_bonus 10 800 300 300 7
   ```