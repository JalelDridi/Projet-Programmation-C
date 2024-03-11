🗳️ Application de Gestion des Élections Municipales
Bienvenue dans l'Application de Gestion des Élections Municipales ! Cette application est conçue pour faciliter différents aspects des élections municipales, y compris la gestion des utilisateurs, la gestion des votes, la gestion des réclamations, la gestion des élections, la gestion des bureaux de vote et la gestion des observateurs. Écrite en C en utilisant le framework GTK+ avec Glade, cette application offre une interface conviviale pour gérer efficacement les tâches liées aux élections.

🚀 Fonctionnalités
Gestion des Utilisateurs : Les administrateurs peuvent gérer les comptes d'utilisateurs, y compris l'ajout, la modification et la suppression des utilisateurs.
Gestion des Votes : Facilite le processus de vote et d'enregistrement des votes de manière sécurisée.
Gestion des Réclamations : Permet aux observateurs de soumettre des réclamations ou des plaintes concernant le processus électoral.
Gestion des Élections : Permet aux administrateurs de superviser et de gérer divers aspects du processus électoral.
Gestion des Bureaux de Vote : Fournit des outils pour gérer les bureaux de vote et assurer un fonctionnement fluide.
Gestion des Observateurs : Permet la gestion et la surveillance des observateurs participant au processus électoral.
🛠️ Installation
Si vous rencontrez des problèmes lors de l'installation des dépendances requises, vous avez deux options :

Installation avec Docker : Utilisez le Dockerfile fourni dans le code source pour créer une image Docker contenant les dépendances nécessaires. Vous pouvez également télécharger directement l'image Docker depuis le lien DockerHub fourni.

Installation Manuelle : Suivez les étapes d'installation manuelle pour vous assurer que toutes les dépendances sont correctement installées sur votre système.

💻 Utilisation
Pour vous connecter à l'espace approprié au sein de l'application, suivez ces instructions :

Exécutez le programme depuis le répertoire "src".
Les données utilisateur sont stockées dans le fichier texte "ajt_ut.txt" situé dans le répertoire "src".
Permissions d'Accès :

Administrateur : Accès à la gestion des utilisateurs, à la gestion des élections et à la gestion des bureaux de vote.
Électeur : Accès à la gestion de la liste électorale et à l'espace de vote.
Agent de Bureau de Vote : Accès à la gestion des observateurs.
Observateur : Accès à la gestion des réclamations.
Dans l'espace de vote :

Si un électeur ne sélectionne aucune option dans le tableau des listes électorales, son vote sera compté comme un vote blanc.
Sinon, l'électeur peut voter en sélectionnant une seule liste.
