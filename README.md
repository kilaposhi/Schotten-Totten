# Big Shotten-Totten

## Liens utiles :
- Le [Trello de l'équipe](https://trello.com/b/XQj4rIn7/shotten-totten)
- Le [Rapport n°1](https://fr.overleaf.com/project/6419a39393e938ac5e40ea3e)(Overleaf)
- Le [Lien UML](https://codimd.math.cnrs.fr/9RFXDxsXSFaQ7eQ6g6FQIQ?both)


## Manip git à faire :

`git clone https://github.com/kilaposhi/Shotten-Totten.git` : Pour copier le repository sur vos machines depuis un terminal comme **git bash**.  
Si vous utilisez Clion, (Ou Visual Studio Code aussi surement), vous pouvez directement faire un nouveau projet depuis un controle de version ("Create project from Version Control").


### Le fichier`.gitignore` :
- Créer un fichier `.gitignore` (ou modifier celui existant) dans lequel on écrira les `path` des fichiers et des directory que `git` doit ignorer.  
Voici un exemple de mon `.gitignore` pour mon cas où j'utilise l'IDE Clion :
```
cmake-build-debug/
CMakeLists.txt
.idea/
```
 **Pourquoi git doit ignorer des fichiers:** Les fichiers `.gitignore` indique à git, les fichiers ou les directory (ex :`directory_sensible/`) à ne pas `push` sur le Github.   
 On écrit donc le nom des librairies, les "CMake" etc...  
 Comme le repository github est **publique**, tout le monde pourrait accéder à notre projet. Comme on ne veut pas que le monde ait accès à nos fichiers de config pour des questions de sécurité, on utilise `.gitignore`.  

>**Remarque :** Une fois qu'un fichier a été `push` sur le repository publique il est très dur de le faire disparaitre totalement, c'est pour cela que l'on prend des précautions.

