# mini_serv

Serveur de chat TCP minimaliste en C — sujet d'examen de l'école 42.

## Description

`mini_serv` écoute sur `127.0.0.1` au port donné en argument et permet à plusieurs clients de communiquer entre eux. Il utilise `select()` pour gérer plusieurs connexions simultanées de façon non-bloquante.

## Fichiers

| Fichier              | Description                                          |
|----------------------|------------------------------------------------------|
| `mini_serv.c`        | Version opérationnelle complète                      |
| `mini_serv_clean.c`  | Version annotée, facile à relire et recopier en exam |
| `main.c`             | Squelette fourni par le sujet (fonctions utilitaires)|
| `Subject.txt`        | Énoncé officiel de l'examen                          |

## Compilation

```bash
cc -Wall -Wextra -Werror mini_serv.c -o mini_serv
```

## Utilisation

```bash
./mini_serv <port>
```

Tester avec `nc` :

```bash
# Terminal 1 — lance le serveur
./mini_serv 8080

# Terminal 2 — client 0
nc 127.0.0.1 8080

# Terminal 3 — client 1
nc 127.0.0.1 8080
```

## Comportement

### Connexion d'un client
Tous les clients déjà connectés reçoivent :
```
server: client %d just arrived
```

### Message d'un client
Le message est retransmis à tous les autres clients, préfixé par :
```
client %d: <message>
```
Un seul message peut contenir plusieurs `\n` — chaque ligne est préfixée séparément.

### Déconnexion d'un client
Tous les clients restants reçoivent :
```
server: client %d just left
```

## Architecture

```
main()
 ├── socket / bind / listen
 └── boucle select()
      ├── fd == sockfd  →  accept()  →  register_client()
      └── fd != sockfd  →  recv()
           ├── bytes <= 0  →  remove_client()
           └── bytes >  0  →  str_join() + handle_message()
                                └── extract_message() × N  →  send_to_all_except()
```

### Fonctions clés

| Fonction              | Rôle                                                       |
|-----------------------|------------------------------------------------------------|
| `register_client(fd)` | Ajoute le fd au master set, attribue un id, notifie        |
| `remove_client(fd)`   | Notifie, free le buffer, retire du set, ferme le fd        |
| `handle_message(fd)`  | Extrait les lignes complètes et les retransmet             |
| `send_to_all_except`  | Envoie une string à tous les fd sauf l'auteur              |
| `extract_message`     | Extrait une ligne (`\n`) depuis un buffer dynamique        |
| `str_join`            | Concatène deux strings avec réallocation (fournie)         |

## Points clés à l'examen

- **`rfds = wfds = afds`** avant chaque `select()` — select modifie les sets en place.
- **`break` après `accept` et `remove_client`** — on ne peut pas continuer à itérer sur un set qui vient d'être modifié.
- **`msgs[fd]`** accumule les données partielles entre deux `recv` — indispensable pour les messages multi-paquets.
- **`wfds`** est utilisé pour vérifier qu'un fd est prêt à recevoir un `send` sans bloquer.
- Le fd du socket serveur (`sockfd`) est lui aussi dans `afds` — c'est lui qu'on teste pour les nouvelles connexions.
