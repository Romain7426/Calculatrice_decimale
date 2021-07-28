# *Calculatrice décimale et sa bibliothèque*

[GLOBISH: https://github.com/Romain7426/Calculatrice_decimale/blob/main/README.eng.md](https://github.com/Romain7426/Calculatrice_decimale/blob/main/README.eng.md)

Bonjour tout le monde! ☺ 

Ce programme est certes une calculatrice, mais une calculatrice décimale. C'est-à-dire que toutes les opérations sont effectuées en virgule fixe et en base dix. Pourquoi? Parce que j'avais envie d'avoir des résultats exacts lors de mes calculs. Et non pas «Oui, compte tenu de la réprésentation interne IEEE-machin, il y a des erreurs d'arrondi, etc.». Et moi, je suis un humain et pas une machine, donc je préfère la base dix à la base deux. 

Peut-être que il existait déjà un tel programme (des choses équivalentes sont nécessairement écrites en cryptographie), mais je n'en avais trouvé aucun, donc j'écrivis le mien. 

NB: Ce programme est loin d'être parfait. 

Toutes les fonctions sont dans une bibliothèque séparée; donc les fonctionnalités peuvent être incorporées dans n'importe quel autre programme. 


## Auteurs  
 
Auteurs: 
 - [Romain: https://github.com/Romain7426](https://github.com/Romain7426)


## [Propriété intellectuelle](https://fr.wikipedia.org/wiki/Propri%C3%A9t%C3%A9_intellectuelle) 
 
Nous ne portons aucun intérêt à la [propriété intellectuelle](https://fr.wikipedia.org/wiki/Propri%C3%A9t%C3%A9_intellectuelle) du présent programme. Vous pouvez faire ce que il vous plaît avec ce programe. 

Nous aurions bien laissé ce programme dans le [domaine public](https://fr.wikipedia.org/wiki/Domaine_public_(propri%C3%A9t%C3%A9_intellectuelle)), mais il semblerait que il existerait une possibilité pour s'approprier du matériel qui serait dans le domaine public, et d'en restreindre l'accès. Afin de prévenir ce cas dégénéré, ce programme a été publié sous une licence équivalente à la [licence ISC](https://fr.wikipedia.org/wiki/Licence_ISC), mais en plus relâchée (cf. le fichier [COPYING](https://github.com/Romain7426/Calculatrice_decimale/blob/main/COPYING) pour la consulter in extenso). En ce qui nous concerne, vous pouvez faire ce que vous voulez avec ce programme et son code, dans la mesure vous n'empêchez personne de l'utiliser, y compris nous-mêmes. 


## Installation et compilation

La procédure: 

<pre>
$ ./tools-compile.sh
$ ./configure.sh
$ make 
$ make install 
</pre>

Les outils devraient compiler sans problème. 

La configuration n'est pas basée sur [GNU Autohell](https://en.wikipedia.org/wiki/Autohell), néanmoins nécessite [GNU Make](https://en.wikipedia.org/wiki/GNU_make) (qui est un langage plus sympathique que le [shell standard](https://fr.wikipedia.org/wiki/Bourne_shell)). Si le fichier './configure.sh' ne le trouve pas, il faut éditer le fichier pour lui indiquer. 

Par défaut, l'installation se fait dans le sous-répertoire './destroot'. Cela peut se changer en éditant le *Makefile*. 

Dans l'ensemble, le programme ne dépend pas de grand chose: un compilateur [C99](https://fr.wikipedia.org/wiki/C_(langage)#Normalisation), et éventuellement [GNU Make](https://en.wikipedia.org/wiki/GNU_make). Faire compiler le programme ne devrait pas poser de problèmes majeurs (testé avec [clang](https://fr.wikipedia.org/wiki/Clang), [gcc4](https://fr.wikipedia.org/wiki/GNU_Compiler_Collection), et [gcc8](https://fr.wikipedia.org/wiki/GNU_Compiler_Collection); hélas [pcc](https://en.wikipedia.org/wiki/Portable_C_Compiler) se plaint).  


## Considérations techniques


base 

int8 

## Vitesse d'exécution

Nous n'avons pas tout testé. Nous avons surtout regardée la division qui l'opération la plus lente, et de loin. 

<pre>
 - Apple — MacBook Air [Mid-2011] 
   Processor: 1.6GHz Intel Core i5-2467M [ https://en.wikipedia.org/wiki/List_of_Intel_Core_i5_processors ] 
   [ 1 ; 65535 ] x [ 1 ; 65535 ] { soit 4294836225 points } -> all succeeded      // Actual count matches: 4294836225 ( 4294967296 - 131071 ) 
   Temps: 23041m27.315s (soit 16,0 jours) soit 1382487.315s 
   Soit: 3106.600818974 divisions par seconde  ((rappel: pour sur un processeur cadencé à 1.6 giga-opérations par seconde, soit 0.5 million [515k] cycles nécessaires…!) 
   Soit: 186396.04913844 divisions par minute 
   Soit: 1 division en 0.000321895 seconde = 1 division en 0.321895 milli-seconde = 1 division en 321.895 micro-secondes 

 - GIGABYTE — MZGLKAP-00 
   Processor: Intel(R) Celeron(R) J4105 CPU @ 1.50GHz [ https://en.wikipedia.org/wiki/List_of_Intel_Celeron_microprocessors ] 
   [ 1 ; 65535 ] x [ 1 ; 65535 ] { soit 4294836225 points } -> all succeeded      // Actual count matches: 4294836225 ( 4294967296 - 131071 ) 
   Temps: 29105m13.69s (soit 20,2 jours) soit 1746313.69s 
   Soit: 2459.372705828 divisions par seconde  ((rappel: sur un processeur cadencé à 1.5 giga-opérations par seconde, soit 0.6 million [610k] cycles nécessaires…!) 
   Soit: 147562.36234968 divisions par minute 
   Soit: 1 division en 0.000406608 seconde = 1 division en 0.406608 milli-seconde = 1 division en 406.608 micro-secondes 
</pre>

Ce n'est pas extraordinaire, mais cela pourrait être pire. 

## Futur & TODOs  

Nous travaillons aléatoirement sur les différents projets en cours. Il est tout à fait probable que ce projet n'avance pas au cours des prochaines années, voire décennies. 

Cela ayant été précisé: 
 - Il faut écrire une fonction de conversion depuis une chaîne de caractères. 
   (Pour l'instant, on convertit en [*float*](https://en.wikipedia.org/wiki/Single-precision_floating-point_format), puis dans le format interne. Ceci entraîne justement les arrondis qui nous voulions éviter, et en plus fait dépendre de la librairie [*math*](https://fr.wikipedia.org/wiki/Math.h). Bref. ☹)
 - Améliorer la [REPL](https://en.wikipedia.org/wiki/Read%E2%80%93eval%E2%80%93print_loop) afin d'avoir un historique et des raccourcis claviers utilisables. 
 - Implémenter une fonction pour calculer les chiffres de [Pi](https://fr.wikipedia.org/wiki/Pi). 
 - Implémenter les fonctions circulaires: *cos*, *sin*, etc. 
 - Implémenter *exp*, *ln*, *sqrt*, *carre*, *power*, etc. 
 - Implémenter un type *string*. 
 - Implémenter des variables (en particulier *ans*). 
 - Implémenter des tableaux. 
 - Implémenter le traitement de données (un fichier *dat* en entrée, et un fichier *dat* en sortie). 
 - Implémenter un lien avec [Gnuplot](https://fr.wikipedia.org/wiki/Gnuplot). 
 - Implémenter une création de fichiers graphiques ([BMP](https://fr.wikipedia.org/wiki/Windows_bitmap)? [PCX](https://fr.wikipedia.org/wiki/PCX)? [Farbfeld](https://tools.suckless.org/farbfeld/)?). 
 - Implémenter une [FFT](https://fr.wikipedia.org/wiki/Transformation_de_Fourier_rapide). 
 - Une [GUI](https://fr.wikipedia.org/wiki/Interface_graphique) simple en [FLTK](https://fr.wikipedia.org/wiki/FLTK). 
 - Une [GUI](https://fr.wikipedia.org/wiki/Interface_graphique) comme celle de [DrRacket](https://fr.wikipedia.org/wiki/Racket_(langage)). 
 - Une [GUI](https://fr.wikipedia.org/wiki/Interface_graphique) de type tableur, comme Excel (parce que c'est très comfortable! ☺). 
 - … 
 - Bref, avoir un truc utilisable! 


Merci!! :smile: 

Et nous vous aimons tous. :kissing_heart: 

 

