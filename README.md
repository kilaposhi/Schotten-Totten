# Big Shotten-Totten

## Liens utiles :
- Le [Trello de l'équipe](https://trello.com/b/XQj4rIn7/shotten-totten)
- Le [Rapport n°1](https://fr.overleaf.com/project/6419a39393e938ac5e40ea3e)(Overleaf)
- Le [Lien UML](https://codimd.math.cnrs.fr/miJRpGXeRKuiDBEZmn28rw?edit)


## Manip git à faire :

`git clone https://github.com/kilaposhi/Shotten-Totten.git` : Pour copier le repository sur vos machines depuis un terminal comme **git bash**.  
Si vous utilisez Clion, (Ou Visual Studio Code aussi surement), vous pouvez directement faire un nouveau projet depuis un controle de version ("Create project from Version Control").

### Le fichier`.gitignore` :
- Créer un fichier `.gitignore` (ou modifier celui existant) dans lequel on écrira les `path` des fichiers et des directory que `git` doit ignorer et ne jamais sauvegarder (ne jamais commit).    
Exemple de `.gitignore` pour mon cas où j'utilise l'IDE Clion :
```
cmake-build-debug/
CMakeLists.txt
.idea/
```
 **Pourquoi git doit ignorer des fichiers:** D'une manière générale on met principalement le **code source** sur git.   
       
 Comme le repository github est **public**, tout le monde pourrait accéder à notre projet. Comme on ne veut pas que le monde ait accès à nos fichiers de config pour des questions de sécurité, on utilise `.gitignore`. 
Exemples de fichiers à indiquer dans le `.gitignore` :
- Fichiers de configurations spécifique à l'IDE ou à l'OS  
- Fichiers contenant des logins, mots de passe pour une BDD, token d'API...
- Les Logs : Servent à débugger, changent tout le temps... 
- Librairies : ce sont des fichiers lourds qu'on ne modifie jamais
- Exécutables, fichiers binaires : Ne sert à rien de les sauvegarder et cause des conflits facilements

>**Remarque :** Une fois qu'un fichier a été `push` sur le repository publique il est très dur de le faire disparaitre totalement, c'est pour cela que l'on prend des précautions.

