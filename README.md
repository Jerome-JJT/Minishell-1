# -   [**C**: _Tutorial - Write a Shell in C_](https://brennan.io/2015/01/16/write-a-shell-in-c/)

## La vie d'un shell
- **Initialiser**: Lit et execute ses fichiers de configuration. Change le comportement du shell.
- **Interpret**er : Ensuite, shell lit les commandes depuis stdin (qui peut aussi etre un fichier) puis les execute.
- **Terminer** : Apres l'execution des commandes, le shell execute les commandes d'arrets, freent la memoire et termine.
``c
int main ()
{
	//initialize : load config files.
	// run command loop -> lsh_loop(); (loop n interpret commands)
	// shutdown n cleanup, free.
	return( EXIT_SUCCESS);
}`


## La boucle shell
Pendant la boucle `lsh_loop`, le shell:
1. Lit les commandes depuis l'entree standard. // `lsh_read_line`
2. Analyse (parsing) : separe la chaine de commande en un programme et des arguments. // `lsh_split_line(line)`
3. Execution : lance les commandes analysees. // `lsh_execute(args)`
Le code de cette boucle imprime un prompt (``>``), appel une fonction qui lit la ligne entree dans le prompt, appel une autre fonction qui split cette ligne (pour recup les args) et une derniere qui execute ces args. 
Elle free la ligne et les args cree en amont. Une variable `statut` est utilisee pour savoir quand sortir de la boucle. Cette valeur est initilisee au debut de la boucle et est modifie dans la derniere fonction appelee (celle qui exectute).

##### 1. Lire la ligne
Strategie: Allouer un espace memoire, si cet espace est insuffisant pour recuperer la ligne entree par l'user, realloquer.
``
```c
char *buffer = malloc(sizeof(char) * bufsize); //allocation
...
    if (position >= bufsize) {  //ligne trop longue
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize); // reallocation
```

Ne pas oublier de controler si l'allocation s'est faite correctement.
Une boucle "infinie" est utilisee. ``'c'`` est un `INT` et non un `CHAR` pour pouvoir etre compare avec le `EOF`, qui est un `INT`.  Buffer est une `str *char`.
Si `c == '\0'` ou `c == '\n'`, on termine la string buffer avec un ``'\0'`` et on le retourne. Sinon, on ajoute le nouveau `c` a la string buffer. 
Si la ligne entree dans `stdin` est plus longue que le buffer, on realloque.
check `getline()`, stdio.h (fait bien ce taff). Mais tenter de faire sans.

Si l'utilisateur tape ctrl + D, cela equivaut a un EOF.
La fonction `lsh_read_line` exit(EXIT_SUCCESS) si le EOF est atteint (soit le EOF d'un fichier, soit le CTRL + D de l'utilisateur). Exit(EXIT_FAILURE) si une erreur apparait, on echoue apres avoir imprimer l'erreur (perror).

##### 2. Parsing, analyse de la ligne
A cet instant, nous avons la ligne entree dans stdin. Il faut maintenant l'analysee (parsing) en liste d'arguments (' ', " ", <, >, | , / etc.).  Il faut tokeniser les arguements a l'aide des differents separeteurs, comme des espaces. 
Une fonction `lsh_split_line` est cree. On lit la ligne, tokenize chaque mot separer par les delimiteurs et on cree le double tableau (commandes + args), on temine ce double tableau par le ``'\0``. Ne pas oublier de realloquer le buffer si la ligne est trop longue (puis d'ajuster la taille du double tableau).
La technique du buffer pouvant s'etendre est appliquee autant pour le parsing que pour la lecture de la ligne (1ere etape).
`strtok()` est equivalant a un split, il renvoit un ptr et termine les tokens par ``'\0'`` . Ces ptr sont sotckes dans un double tableau.  Ce tableau est realloque si necessaire. Quand `strtok()` ne retourne plus de tokens, la liste de tokens est termine par ``'\0'`` (derniere case du tableau).
La fonction ``getenv`` recherche une variable dans l’environnement. Peut etre utile pour le parsing.
La fonction ``setenv`` définit la valeur d’une variable d’environnement.

Voir : Token Recognition: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_03

##### 3.  Execution
La fontion principale d'un shell est d'executer des process. 2 types de process (init, le process du kernel) et les process fait avec `fork()`. 
-> voir ``exec()`` et ses variantes: remplace le programme en cours par un nouveau programme. Quand ``exec()`` est appele, le système d’exploitation arrête le processus, charge le nouveau programme, et commence celui-ci à sa place. Un processus existant se divise en deux processus distincts. Ensuite, l’enfant utilise `exec()` pour se remplacer par un nouveau programme. Le processus parent peut continuer à faire d’autres choses, et il peut même garder un œil sur ses enfants, en utilisant le système call `wait()`. Utiliser `perror` avec exec() puis exit.

L'execution se composent de plusieurs fonctions. 
- Une pour le fork prenant en parametre la liste des args precedemment cree. Les enfants lancent les commandes donnee par l'utilisateur.  (`lsh_launch`)
- les builtins
- La fonction qui execute (`lsh_execute`).

###### Shell Builtins
Programmes constuits a l'interieur meme du shell et pas propre aux process. 
Si on veut changer de répertoire, il faut utiliser la fonction `chdir()`. Le répertoire courant est une propriété d’un processus. Si on écrit un programme appelé `cd` qui change de répertoire, il change juste  son propre répertoire courant, puis se termine. Le répertoire actuel de son processus parent reste inchangé. Au lieu de cela, le processus shell lui-même doit exécuter `chdir()`, afin que son propre répertoire courant soit mis à jour. Les processus enfants  lances par la suite hériteront aussi de ce répertoire.
ex: `exit`, `cd`, `help`.

###### Assembler process et builtin
- Creer une fonction qui lance un process ou un builtin. Controle si la commande est une builtin, si oui, elle l'excecute, sinon, elle appelle une autre fonction qui lance un process (`lsh_launch`, `fork`, et `exec` par un child).
- Attention si `argv[0] == NULL` (utilisateur entre un str vide ou juste des espaces) -> doit retourner 1.

## Notes : Library
-   `#include <sys/wait.h>`
    -   `waitpid()` and associated macros
-   `#include <unistd.h>`
    -   `chdir()`
    -   `fork()`
    -   `exec()`
    -   `pid_t`
-   `#include <stdlib.h>`
    -   `malloc()`
    -   `realloc()`
    -   `free()`
    -   `exit()`
    -   `execvp()`
    -   `EXIT_SUCCESS`, `EXIT_FAILURE`
-   `#include <stdio.h>`
    -   `fprintf()`
    -   `printf()`
    -   `stderr`
    -   `getchar()`
    -   `perror()`
-   `#include <string.h>`
    -   `strcmp()`
    -   `strtok()`

###### Autres details concerant de possibles erreurs futures
- La page de manuel de `getline()` spécifie que le premier argument devrait être libre, donc la ligne devrait être initialisée à NULL dans l'implémentation `lsh_read_line()` qui utilise `getline()`.

- ----------------------
------------------
--------------------

# -   [**C**: _Let's build a shell!_](https://github.com/kamalmarhubi/shell-workshop)

## 1. Lecture de la ligne de l'utilisateur
- `getline`

## 2. Appel systeme
Pour executer une commande entree par un utilisateur, le noyau peut aider. Il est en charge de la plupart des choses liées aux processus.

Les programmes parlent au noyau par le biais des appels système.
Exemples:
- ouverture de fichiers (`open`)
- lire et écrire pour eux (`read`, `write`)
- envoyer et recevoir des données sur le réseau. (`sendto`, `recvfrom`)
- programmes de démarrage (`execve`), `execp` est une fonction wrappe de `execve`.

## 3. Lancer un programme
Les arguments: Quand un programme se lance, il recoit une tableau d'arguments donne par l'utilisateur (argv). Le premier argv est le nom du programme. Ainsi, quand on lance `ls - l /tmp`,  la fonction/programme ls recoit comme argv {"ls", "-l", "/tmp"}.
Equivalent a - >`` execvp('ls', ['ls', '-l', '/tmp'])``
`int execvp(const char*file, char *const argv[]*)``

Exemple d'une fonction de parsing: 
```c char* next_non_empty(char **line)
{
  char *tok;

  /* Consume empty tokens. */
  while ((tok = strsep(line, TOKEN_SEP)) && !*tok);

  return tok;
}


cmd_struct* parse_command(char* str)
{
  /* Copy the input line in case the caller wants it later. */
  char* copy = strndup(str, MAX_LEN);
  char* token;
  int i = 0;

  /*
   * Being lazy (Rule 0) and allocating way too much memory for the args array.
   * Using calloc to ensure it's zero-initialised, which is important because
   * execvp expects a NULL-terminated array of arguments.
   */
  cmd_struct* ret = calloc(sizeof(cmd_struct) + MAX_LEN * sizeof(char*), 1);

  while ((token = next_non_empty(&copy))) {
    ret->args[i++] = token;
  }
  ret->progname = ret->args[0];
  ret->redirect[0] = ret->redirect[1] = -1;
  return ret;
}
```
## 4. Forking, new process
Fork et faire excev dans les process enfants.
- `wait(NULL)``;

## 5. Builtins
Fonctionement du process:
Chaque proces possede sa propre memoire et des métadonnées supplémentaires que le noyau gère, mais que le processus ne peut pas changer directement. Il peut les changer avec des appels système ( user id (`setuid`), group id (`setgid`), priority (`setpriority`), working directory (`chdir`))

Ce qui se passe si `fork` et `exec` du process `/bin/cd`.

```c
1) parent: pid 1000, working directory /tmp
---- fork ----
2) parent: pid 1000, working directory /tmp
   child: pid 2000, working directory /tmp
---- exec `/bin/cd /home/awesome` in child ----
3) parent: pid 1000, working directory /tmp
   child: pid 2000, working directory /tmp/awesome
---- child exits ----
4) parent: pid 1000, working directory /tmp
```

Les process peuvent uniquement utiliser des appels systemes pour modifier leur propre etat. L'enfant change de repertroire, mais pas le parent.
Pour modifier le répertoire de travail du shell, **le shell lui-même doit appeler l’appel système `chdir`.** Il doit traiter une commande cd spécialement : si la commande est ``cd``, il faut appeler `chdir` au lieu de fork/exec . La manipulation du cd est  est built in shell – c’est un builtin.

##### Liste des builtins
     builtin, !, %, ., :, @, {, }, alias, alloc, bg, bind, bindkey, break,
     breaksw, builtins, case, cd, chdir, command, complete, continue,
     default, dirs, do, done, echo, echotc, elif, else, end, endif, endsw,
     esac, eval, exec, exit, export, false, fc, fg, filetest, fi, for,
     foreach, getopts, glob, goto, hash, hashstat, history, hup, if, jobid,
     jobs, kill, limit, local, log, login, logout, ls-F, nice, nohup,
     notify, onintr, popd, printenv, pushd, pwd, read, readonly, rehash,
     repeat, return, sched, set, setenv, settc, setty, setvar, shift,
     source, stop, suspend, switch, telltc, test, then, time, times, trap,
     true, type, ulimit, umask, unalias, uncomplete, unhash, unlimit, unset,
     unsetenv, until, wait, where, which, while

Certaines de ces commandes peuvent aussi etre appeler en externe, comme echo. 

## 6. Pipes
##### Exemple:
```c
ls | wc
```

##### Les bases:
- Le fd sont des int (`0` is stdin, `1` is stdout, `2` is stderr)
```c
int pipe_fds[2];
pipe(pipe_fds);  // puts returns [4, 5] in pipe_fds
```
- Pipe[1] -> ecriture, pipe[0] -> lecture
- If `pipe` returns `[4, 5]`, then any data written to `5` can be read out of `4`. ([1] == [5], [0] == [4])
- we need to set `ls`'s stdout to be `5` and `wc`'s stdin to be `4`
- We'd need to run `dup2(5, 1)` for `ls` and `dup2(4, 0)` for `wc`.

##### Recapitualtion pour creer un pipe 'ls | wc'
- 1. Creer pipe (`pipe()`)
- 2. Fork 2 fois (car 2 commandes)
```c
parent: pid 1000, stdin: terminal, stdout, terminal
---- fork twice ----
parent: pid 1000, stdin: terminal, stdout: terminal
child 1: pid 2000, stdin: terminal, stdout: terminal (for `ls`)
child 2: pid 3000, stdin: terminak, stdout: terminal (for `wc`)
```
- 3. child 1 lance `dup2(pipe_fds[1], 1)` et exec `ls`
- 4. child 2 lance `dup2(pipe_fds[0], 0)` et exec `wc`
- 5.  Fermer les deux sorties du pipe dans le process parent.

## 7. La suite
##### Progression naturelle
- Gerer les mutlitples pipes :)
- Gerer les redirection ''>'': `grep shel /usr/share/dict/words > /tmp/shel_words`
	Pour cela il faut etendre le parsing afin de recuperer les redirections. (Gestion similaire aux redirections des pipes). Il faut utiliser `open` a la place de `pipe` pour avoir les fd a lire ou a ecrire dedans.
- Rediriger les autres fd: si on lance  `some-command 2>/tmp/errors` dans un shell, on lui demande de rediriger stderr (fd 2) vers `/tmp/errors`. Utile pour capturer la sortie du journal lorsqu’une commande l’écrit sur stderr.
-  Redirection vers d’autres fd: si on lance `some-command 2>&1`  dans un shell habituel, les données écrites par some-command sur son stderr (fd 2) iront au même endroit que son stdout (fd 1).

##### Autres directions
- Expension des variables d'environnement: Comparer la sortie de `echo $HOME` avec celle d'un shell et d'un minishell. Le shell traite les tokens commencant par ``$`` specialment, il les rechercher par leur nom dans l'environnement puis les remplaceme (un peu comme les alias des makefile). La fonction `getenv` recherche une variable dans l’environnement. Elle peut etre utile pour le parsing.
- Définition des variables d’environnement sur les processus enfants: Comparer la sortie de - `date` et `TZ=Pacific/Samoa date` d'un shell et d'un minishell. La commande `date` utilise la variable d'environnement `TZ` pour le choix de l'affichage de la date. Préfixer une commande avec un string comme `VAR=value` définit VAR à value dans l’environnement de l’enfant. La fonction `setenv` définit la valeur d’une variable d’environnement. Il faudra modifier la fonction parsing pour trouver ces préfixes.
- Le builtin `export`: Permet de changer la valeur d’une variable d’environnement dans le shell lui-même. Comme avec cd, parce qu’un enfant ne peut pas modifier l’environnement de son parent, l’exportation doit être un builtin.
- Gestion des signaux: Comparer le resultat de la commande `^C` (control-C) entre un shell et un minishell.`^C` envoie un signal a notre process (dans ce cas au process `SIGINT`). Les signaux interompent l'execution du programme. Annule le process par defaut.  Pour éviter cela, on peut enregistrer une fonction de gestion de signal à appeler lorsque `SIGINT` est reçu, ou décider de l’ignorer.
- Globbing (utilisation de wildcard, asterix): Comparer la sortie de la commande `wc -c *` dans un shell et un minishell. La fonction `glob` de la libraty ``<glob.h>`` sera utile.
- Lancer une commande en arriere plan: Dans un shell, terminer une commande avec ``&`` la lance en arriere plan. La commande s'execute, mais le shell ne la bloquera pas pendant le lancement. Il n'attendra pas le processus enfant dans ce cas.

-----------------
--------------
------------------

#  - [**C**: _Writing a UNIX Shell_](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/)

Definition d'un shell : Un shell est un interface qui permet d'interagir avec le noyau d'un systeme d'exploitation.

## 1. Fonctionnement d'un shell
Le shell analyse (parse) des commandes entrees par un utilisateur et les executent. Pour etre en mesure de le faire, le processus du shell ressemble a:
- 1. Demarrage du shell
- 2. Attente d'une entree d'un utilisateur.
- 3. Analyse (parsing) de l'entree.
- 4. Execution et retour d'un resultat.
- 5. Retour a l'etape 2, attente d'une entree.

Les process sont la piece centrale de cet edifice. Le shell est le process PARENT. C'est le fil conducteur du programme qui attent les entrees de l'utilisateur. On n'execute cependant pas les commandes dans le processus PARENT pour les raisons suivantes:
- Une commande erronnee terminera le shell entier. 
- Les commandes independantes possedent leur propre block process. Cela est connue sous les terme "isolation" et tolerance aux pannes -> L’isolation des processus est un ensemble de différentes technologies matérielles et logicielles conçues pour protéger chaque processus des autres processus du système d’exploitation.

## 2. Fork
Les forks sont utiles pour isoler les process. Ils creent une copie du process actuel (child) qui possede sa propre ID (PID) ainsi que leur propre espace memoire. 

![[Pasted image 20230511160428.png]]

Le deux process continuent leur execution independamment l'un de l'autre.

## 3. Introduction au determinisme
L'appel systeme ``sleep`` ->  suspend l'execution pendant un intervalle de temps (en secondes).

Sleep avec un process parent:
```c
int main() {
    pid_t child_pid = fork();

    // The child process
    if (child_pid == 0) {
        printf("### Child ###\nCurrent PID: %d and Child PID: %d\n",
               getpid(), child_pid);
    } else {
        sleep(1); // Sleep for one second
        printf("### Parent ###\nCurrent PID: %d and Child PID: %d\n",
               getpid(), child_pid);
    }
 
    return 0;
}
```

La sortie donnera:
```c
### Child ###
Current PID: 89743 and Child PID: 0
```
et une sconde plus tard apparait:
```c
### Parent ###
Current PID: 89742 and Child PID: 89743
```
Ce comportement sera le meme a chaque lancement, le processus enfant a assez de temps pours s'executer meme sans fonction `wait` dans le parent. Attention car le parent peut terminer son execution avec que l'enfant termine le sien.

## 4. Le determinisme fait correctement
Utiliser ``sleep`` pour gerer le flux d'execution du process n'est pas toujours la meilleure approche.
- Qu est-ce qui garanti que peu importe ce qui est attendu finira son execution en n secondes ?
- Et ci cela se termine plus tot que prevu ? Cela cause un ralentissement superflu.
Dans certains cas, il vaut mieux utiliser ``wait`` (attend until un enfant a fini) ou ``waitpid`` (attend un enfant specifique). L'appel ``wait(&wstatus)`` equivaut a ``waitpid(-1, &wstatus, 0)``.
``waitpid`` prend 3 parametres: le PID du process a attendre, une variable qui sera remplie avec des informations sur la façon dont le processus a été terminé et des options flags (pour customiser le comportement de ``waitpid``).

exemple:
```c
int
main() {
    pid_t child_pid;
    pid_t wait_result;
    int stat_loc;

    child_pid = fork();
        
    // The child process
    if (child_pid == 0) {
        printf("### Child ###\nCurrent PID: %d and Child PID: %d\n",
               getpid(), child_pid);
        sleep(1); // Sleep for one second
    } else {
        wait_result = waitpid(child_pid, &stat_loc, WUNTRACED);
        printf("### Parent ###\nCurrent PID: %d and Child PID: %d\n",
               getpid(), child_pid);
    }
 
    return 0;
}
```

--------------
-----------------
------------

#  -   [**C**: _Build Your Own Shell_](https://github.com/tokenrove/build-your-own-shell)

## 1. Fork/exec/wait

### La boucle: pseudo-code
```c
loop
    print "$ "; flush(stdout)
    line = getline(stdin).split()
    if eof(stdin): exit(0)
    pid = fork()
    if pid == 0:
      execvp(line)
    waitpid(pid)
```

##### Les bases
- Minishell doit ecrire ``$`` dans le prompt.
- Minishell doit accepter une line d'entree et la diviser.
- Si le premier mot est un Builtin (commande gerer par le shell meme et non par un programme externe), il faut l'appeler. Sinon il faut l'executer comme une commande avec des arguments delimites par l'espace.
- Repeter jusqu'a la reception de l'EOF sur stdin.

##### Executer une commande
Il faut tout d'abord faire un ``fork``. Faire `execve` dans le child pour executer la commande avec ses arguments. Le parent attend que l'enfant finisse avec `wait`. Cela laisse le shelll dormir pendant que la commande s'execute, il se reveille grace au statut exit de cette meme commande.

##### (
##### Faire des tests
Tester des commandes comme cat, pwd, echo, true, false.
##### )

##### Chercher le chemin / path
- Voir pipex
- `getenv`

##### Status exit et !
On obtient le satuts exit de l'enfant grace a `wait`. Conserver ce status qui sera utile par la suite. En relation avec les commandes: `/bin/true` et `/bin/false`.
Beaucoup d'informations sont retournees avec `wait`. Seulement exit status nous interesse. (0 = sucess, autre = echec). Si le premier mot que nous lisons est ``!``, le status de sortie qui suit est annule. Ceci est un mot et pas un caractere. ``!true`` retourne un exit code non-zero. 
Mettre les codes exit non-0 en rouge pour mieux reperer les erreurs.

##### Liste des commandes
Diviser son entree avec ";", '&&' et "||". Les commandes sperarees par ces signes sont executees sequentiellement. 

Quand 2 commandes sont separees par ``&&``, on doit lancer cette derniere seulement si l'exit status de la premiere commande est != 0.

Pour plus d'infos sur les listes sequentielles : https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_09_03

##### Exec builtin
Il est possible d'utiliser `fork` sans `exec` et l'inverse. L'utilisation de `exec` builtin fera en sorte que shell `exec` sans forker et remplacera entierement le process actuel.
Pratique en scripting, lorsque l'on veut jeter la memoire occupee par le shell car la prochaine commande est la derniere faite.

##### Subshells
Utiliser `fork` sans `exec`, tout en attendant avec `wait`, permet des manoeuvres dans un environnement shell isole. Si une commande est entree paratheses, on fork, le parent attend l'enfant et l'enfant execute la commande normallement. 
```c
(cd /tmp && pwd); pwd
```
Mettre ``/tmp`` peut importe le repertoire de travail anterieur.

##### Ligne continue
Charactere continu: mettre ``\`` a la fin de la ligne. Imprimer ``>`` en tant que prompt lors de la lecture d'une ligne continue.
Si une ligne se termine par ``&&`` ou ``||``, on souhaite aussi continuer a lire la ligne suivante de la meme liste.

## 2. Files et pipes
Il faut diviser ces pipelines par occurrances de ``|``, et pour chaque commande, trouver des expressions de la forme `n< path, n> path, et n>> path`, où n est un entier optionnel (fd?)
Si le dernier element lu est un pipe, on continue de lire jusqu'a la prochaine ligne, comme avec ``||``, ``&&`` et ``\``.

Pour gerer les quotes: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_10

Pour chaque paire de commandes connectees par un ``|``, appel `pipe()`, remplacer fd[1] par pipefd[0] et fd[0] par pipefd[1].
Pour chaque redirections d'entree et de sortie (``<`` et compagnie), on utilise un `open`.
-> Lire : (`O_RDONLY`) pour `<`
-> Ecrire: (`O_CREAT|O_TRUNC|O_WRONLY`) pour `>`
-> Lire et ecrire  pour `<>`
-> Ajouter/joindre: (`O_CREAT|O_APPEND|O_WRONLY`) pour `>>`
Fermer les fd non utilise le plus tot possible.

**Bug a controler**: Faire `echo foo | cat | cat`, doit s'executer immediatement, sinon, une sortie de pipe n'a pas ete fermee quelque part. 

### Tableau resume des redirections

![[Screen Shot 2023-05-12 at 11.40.31 AM.png]]

### Gerer les fd des enfants
Utiliser l'option `CLOEXEC`, cela va fermer les fd apres l'exection `excev`. 
Utiliser l'outil `lsof` pour debugger les probelmes de redirection des fd. 

## 3. Controls et signaux
-   [`sigaction`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/sigaction.html)
-   [`tcsetpgrp`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/tcsetpgrp.html)
-   [`setpgid`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/setpgrp.html)
-   [`tcgetpgrp`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/tcgetpgrp.html)
-   [`killpg`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/killpg.html)
-   [`isatty`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/isatty.html)

### Les process en arriere-plan
Les commandes finissant par un `&` s'executent en arriere plan. Il faut etendre la gestion de l'entree de l'utilisateur a ces cas. Il n'est pas necessaire de `wait` ce types de commandes.
Quand un enfant meurt, le parent est notifie par un `SIGCHILD`. `libev` peut etre utile pour la gestion des sigaux.

### Les groupes de process
Groupe de process = job. Ex: Pipe.
A la creation d'un pipe, le 1er child se met lui-meme dans ce groupe de process grace a `setpgid(getpid(), getpid())`. Tous les autres child de meme grace a `setpgid(getpid(), pgrp_of_pipeline)`. Les parents doivent garder une trace des PID des child et faire en sorte que les autres child y ont acces. 
On peut `kill()` un groupe entier avec `SIGCONT` et pas seulement juste un child.

### Groupe de process a l'avant-plan
CTRL + C = `^c`
Comment utiliser cette commande pour fermer le process et non le shell entier ? `tcsetpgrp` dit au driver tty (donnees entrees manuellement sur le clavier et non par un programme,  et qui traduit `^c` en `SIGINT`), que le groupe de process donnee est celui en charge du terminal a ce moment.
`tcsetpgrp` doit etre fait dans les parents et leur enfants. 
Et surtout, il faut retourner `tcsetpgrp`  au groupe de processus du shell chaque fois que CTRL retourne au shell : quand un enfant de premier plan sort ou est arrêté.

### Signaux
`SIGTSTP`: Est envoye a un process par son terminal de controle pour lui demander de s'arreter temporairement.
`SIGTTIN`: Tres similaire a `SIGTERM` -> Requete a un programme de terminer. Signal par defaut de `kill()`
`SIGTTOU` : Similaire a `SIGTTIN` -> généré lorsqu’un process dans un job en arriere-plan  tente d’écrire sur le terminal ou de définir ses modes.
`SIGCONT`:
Lorsque `SIGTSTP` est envoyé à un processus, le comportement habituel est de mettre ce processus en pause dans son état actuel. Le processus ne reprendra son exécution que s’il reçoit le signal `SIGCONT`.  `SIGCONT` est utilisé pour le contrôle des tâches (job control) dans l’interpréteur de commande Unix, entre autres.

Les sigaux sont a gerer apres chaque fin de pipe ou quand les pipes sont mis en arriere-plan.
  `"cmd | cmd | cmd" thing`.
 * Commandes executees en commandes de subsitution ("`cmd`") ont `SIGTTIN`, `SIGTTOU`, `SIGTSTP`  regle sur `SIG_IGN`.
 * Les commandes ordinaires ont des signaux regle sur `SIG_IGN/DFL` comme hérités par le shell de son parent. 
 - Les signaux differents de `SIG_DFL`
	 * `SIGQUIT`: ignore
	 * `SIGTERM` (interactive): ignore
	 * `SIGHUP` (interactive):  envoie `SIGCONT` aux job (groupe de process) termines, envoie `SIGHUP` a tout les autres job et quitte (exit).Quand on exit, il faut envoyer `SIGHUP` aux child. Mais d’abord, il faut s'assurer qu’ils ne sont pas arrêtés, il faut d'abord envoyer `SIGCONT` à tous et ensuit  `SIGHUP`.

Vous pouvez implémenter la fonction intégrée `disown` pour supprimer un emploi de la liste des emplois actifs, de sorte qu’il ne sera pas envoyé HUP dans ce cas.
- `SIGTTIN`, `SIGTTOU`, `SIGTSTP` (if job control is on): ignore
- ^Z (CTRL + Z) est gere non en piegeant `SIGTSTP`, mais en voyant que tout les membres du pipe sont stoppes. 
* `SIGINT` (interactive): Attend le dernier pipe.  Ignore le reste de la ligne de commande, montre le prompt. ^C n'envoie pas `SIGINT` au shell interactif pendant que le shell attend un pipe, since shell is bg'ed (n'est pas dans un groupe de process de premier plan)

### Job control
Grader la traces de job en arriere-plan.
`fg` apporte le job en arriere-plan le plus recent au premier plan. (faire la danse  `tcsetpgrp` , envoyer `SIGCONT` si elle a ete stoppee et attendre avec `waitpid` ). `^z` envoie `SIGTSTP` a un job de premier plan et le suspend. `waitpid` informe si le child a ete suspendu. Il faut garder la trace des job stoppes.
`bg` met le job le plus recemment stoppe en arriere-plan: il faut lui envoyer `SIGCONT` (et garder la trace), mais pas le rendre au TTY (teletype, donnees entrees manuellement sur le clavier et non par un programme).

## 4. Quoting, environnement, variables et extensions
##### Utiles:
- un type de carte (map)
- `getpwnam(3)`
- `glob(3)`
- un moyen d'avoir l'environnement.

### Variables d'environnement
Ameliorer parsing pour gerer le `=` relatif aux variables d'environnement.

##### L'exportation des variables d'env
`export`. Lorsqu'une variable a ete exportee, elle reste exportee. Ces variables exportees seront passees au process child, tandis que les variables non-exportees seront uniquement visibles dans le shell actuel.

Au début du programme, l’environnement indique l’environnement initial.
 * `putenv` ajoute de nouveaux pointeurs, `unsetenv` les supprime.
 * Aucun de ces 2 la (de)allocte des strings.
 * `setenv` alloue de nouvelles strings dans l’espace malloc et fait `putenv`, et donc `setenv` est inutilisable (leaks) pour les besoins de shell.

### Parametres speciaux
Reconnue avec le symbole `$`. Elles sont souvent utilisees pour les scripts.
`$?` s'etend au status exit du dernier pipe utilise.
`$$` s'etend au PID du shell actuel.
`$!` s'etend au PID de la commande en arriere plan la plus recente.

### Quoting
- Ne pas perdre son temps avec la perfection. 
- L'essentiel est de comprendre la difference en les singles et les doubles quotes.
ex: 
``"foo$(echo "$bar")baz" `` est secure, ``"foo"$bar"baz"`` ne l'est pas.
Voir: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_02

### Heredocs
Mettre ``<<word_delimiter`` (ouverture du hererdoc)
texte
texte
...
`word_delimiter` (fermeture du heredoc)

Exemple:
```c 
sudo -u postgres psql <<EOF
CREATE DATABASE $DATABASE_NAME;
CREATE USER $DATABASE_USER WITH PASSWORD '$DATABASE_PASSWORD';
GRANT ALL PRIVILEGES ON DATABASE $DATABASE_NAME TO $DATABASE_USER;
EOF
```

Utile lorsque l'on a besoin d'un fichier d'entree multi-lignes et garde uniquement dans un code local  qui utilise ce meme fichier.
C'est un ennemi potentiel du parsing. Utilisation de `hush`:  Creer un pipe, faire un fork pour obtenir un child qui ecrit le contenu du heredoc dans ce pipe.

### Tidle ~ expansion
`~` seul ou suivi d'un slash s'etend a la valeur de la variable d'env `HOME` : `~/foo` devient `/home/me/foo`
`~user` s'etend au repertoire d'acceuil de l'utilisateur, comme `getpwnam(3)

### Extras
Le prompt doit etre configurable avec la variable d'env `PS1
La variable d'env `PS2` doit controler la continuation du prompt (celle que l'on print apres chaque ligne finissant par `//`)

## Interactivite
### Utiles
##### Termios
Les fonctions `termios` décrivent **une interface de terminal générale fournie pour contrôler les ports de communication asynchrones**. (asynchrones: Se dit de phénomènes, de tâches, de signaux ou d'informations dont les rythmes propres ne sont pas égaux.)
Structure `termios`: Beaucoup des fonctions décrites ici ont un argument termios_p qui est un pointeur vers une structure termios. Identifier si un fd est associé à un terminal.

##### Fonctions pour le controle du terminal
`tcdrain`: Attend que toutes les sorties envoyees aux fichies soient reellement envoyees au terminal.
`cfmakeraw`: Définit le terminal à quelque chose comme le mode "brut" l’entrée est disponible caractère par caractère, l’écho est désactivé et tout traitement spécial des caractères d’entrée et de sortie du terminal est désactivé.
`tcgetattr`: Pour obtenir les attributs d'un terminal (structure `termios`). ``tcgetattr()`` peut fonctionner en avant-plan ou en arrière-plan ; cependant, si le processus est en arrière-plan, un processus d’avant-plan peut ensuite changer les attributs. ``tcgetattr()`` ne fonctionne que dans un environnement où il existe un terminal de contrôle, ou stdin et stderr font référence aux périphériques tty. Plus précisément, il ne fonctionne pas dans un environnement TSO.
`tcsetattr`: Définit les paramètres associés au terminal auxquels font référence les fildes (fd?) de descripteur de fichier ouvert (un descripteur de fichier ouvert associé à un terminal) à partir de la structure termios.
`isatty`: Controle si stdin est un tty (donnees entrees manuellement sur le clavier et non par un programme).

### Editer une ligne
- En premier lieu, empecher l'utilisateur de faire des retour en arriere sur le prompt.
- Sauvegarder les attributs du terminal avec `tcgetattr`.  Cela servira plus tard a restaurer les choses faites. Faire une copie de cela et ensuite `cfmakeraw` cette copie. Puis `tcsetattr` avec les attributs modifies.
- Le terminal est maintenant en mode brut. On lit les characteres un a un, echo si ils sont imprimables et gerer les characteres qui nous interessent. On commence par les retour en arriere (ascii 127). On doit garder un trace de ou on se situe sur l'ecran, et déplacer le curseur à mesure que les caractères sont insérés et supprimés.
- Quand on dessine un prompt, garder une trace d'ou termine le curseur. Quand on repere des retour en arriere (127), empêchez le curseur de se déplacer avant cette position.
- Grace a la trace de la position du curseur, on peut utiliser `SIGWINCH`.
- On annulera cela ("deprep", en termes de readline) chaque fois qu'on execute une commande de premier plan, et bien sûr en sortant du shell.
- Ajouter `^A`, `^E`, `^W`, `^F`, `^B` si necessaire pour minishell.

### Historique
Garder une trace de chaque entree dans le shell (aussi les lignes multiples, heredoc?)
Ajouter `^R`, haut, bas, et historique si necessaire.

### Realisation, fin
Quand on recoit une tab, `^I`, il faut savoir ou l'on se trouve dans la ligne d'entree actuelle: si nous sommes dans une commande, on voudra terminer depuis le contenu de `PATH`, sinon, nous terminerons depuis des fichiers arbitraires, incluant ceux du repertoire actuel. Si nous sommes deja au `/`, nous savons ou chercher (fichier binaires)

##### Utiles

Documentations bash: https://aosabook.org/en/v1/bash.html




