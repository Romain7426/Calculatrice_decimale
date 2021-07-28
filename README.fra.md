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


## Compilation



## Considérations techniques


base 

int8 

## Vitesse d'exécution



## Futur & TODOs  

Nous travaillons aléatoirement sur les différents projets en cours. Il est tout à fait probable que ce projet n'avance pas au cours des prochaines années. 

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

 

