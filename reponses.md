# Chapitre 3 - Un premier serveur TCP

> **1. Après y avoir connecté un client, quittez votre serveur (Ctrl+C) et relancez le. Que se passe-t-il ?**
- Lors du premier démarrage du serveur, l'appel de `nc localhost 8080` affiche le message de bienvenue

- Relancer la commande `nc` affiche plusieurs fois le message

- Relancer le serveur puis `nc` affiche toujours le message

- Quitter puis relancer le serveur alors que la connexion cliente renvoie une erreur `accept client_socket: Bad file descriptor`

---


> **2. Changez votre envoi de message de bienvenue pour envoyer les 10 lignes par 10 appels à la fonction write et ajoutez un petit délai avant l’envoi du message de bienvenue (1 seconde).  
Puis, exécutez la commande suivante :  
    ```
    nc -z 127.0.0.1 8080
    ```  
Que se passe-t-il ?
Que fait l’option -z de la commande nc (lisez le manuel) ?  
Après y avoir connecté un client, quittez votre serveur (Ctrl+C) et relancez le. Que se passe-t-il ?**

- Que se passe t-il : Le serveur semble avoir reçu la connexion de la commande `nc`, car après connexion, le serveur semble s'arrêter.
De plus, dû à la boucle on ne peut connecter qu'une socket à la fois. 

-  \-z `Only scan for listening daemons, without sending any data to them.`
L'option -z permet donc de se connecter à un serveur sans envoyer de données...

---

> **3. Exécutez la commande suivante : telnet ::1 8080. Que se passe-t-il ? Pourquoi ?**

Le serveur n'accepte pas la connexion, car c'est un format d'adresse IPV6 (Il est actuellement défini sur une IPV4).

> **4. Lancez deux clients simultanément. Que se passe-t-il ? Pourquoi ?**

La connexion s'effectue sur les deux clients, mais la reception des messages de bienvenue se font en differés (Probablement à cause de la boucle while)