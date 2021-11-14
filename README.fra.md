# Calculatrice décimale et sa bibliothèque

[GLOBISH: https://github.com/Romain7426/Calculatrice_decimale/blob/main/README.eng.md](https://github.com/Romain7426/Calculatrice_decimale/blob/main/README.eng.md)

Bonjour tout le monde! ☺ 

Ce programme est certes une calculatrice, mais une calculatrice décimale. C'est-à-dire que toutes les opérations sont effectuées en virgule fixe et en base dix. Pourquoi? Parce que j'avais envie d'avoir des résultats exacts lors de mes calculs. Et non pas «Oui, compte tenu de la réprésentation interne IEEE-machin, il y a des erreurs d'arrondi, bla bla bla, etc..». Et moi, je suis un humain et pas une machine, donc je préfère la base dix à la base deux. 

Peut-être que il existait déjà un tel programme (des choses équivalentes sont nécessairement écrites en cryptographie), mais je n'en avais trouvé aucun, donc j'écrivis le mien. 

NB: Ce programme est loin d'être parfait. 

Toutes les fonctions sont dans une bibliothèque séparée; donc les fonctionnalités peuvent être incorporées dans n'importe quel autre programme. 

## Example

<pre>
$ ./destroot/bin/calc-decimal --repl 3> ./stdlog.txt 
> (1002/1000)*3
3.006
> ^D
</pre>

<pre>
$ ./destroot/bin/calc-decimal                         
./destroot/bin/calc-decimal: Decimal calculator.
Usage: ./destroot/bin/calc-decimal [<options>] [<infile>] 
  <infile> can be a filename or '-' for stdin (use './-' for a file named '-')
Options:
  -h,-?,--help,--usage                    Display this help
  --copyright,--license,--licence         Display the program license
  --copyright-cstr                        Display the program license as a C string
  --copyright-cstr_macro                  Display the program license as a C string that can be included in a pre-processor macro
  --copyright-ccomment                    Display the program license as a C comment
  --copyright-shell_comment               Display the program license as a SHELL comment
  --copyright-slash_comment               Display the program license as a double-slash comment
  -v,--verbose                            Increase verbosity
  -q,--quiet,--mute                       Do not tell anything
  -V,--version                            Print program version
  --example,--exemple                     Print an example
  --url                                   Print url
  --tests,--test                          Run some tests
  --repl                                  Run as a REPL (Read-Eval-Print-Loop)
  --stduser <file>                        Redirect all the talk to the user to <file>. (Default is stderr.) (Use 'stdout', 'stderr', and 'stdnull' to redirect to stdout, stderr, and /dev/null.)
  --stdprint <file>                       Redirect textual output data to <file>. (Default is stdout.) ('stdout', 'stderr', 'stdnull' to redirect to stdout, stderr, /dev/null.)
  --stddata <file>                        Non-textual output data is not printed on terminal. Redirect to <file>. (Default is fd 4 - get it by '4>&1' or '4>./data.txt'). ('stdout', 'stderr', 'stdnull' to redirect to stdout, stderr, /dev/null.)
  --stdlog <file>                         Write stdlog to <file>. (By default, stdlog fd is 3; therefore the output of stdlog can be gotten using '3>&2' or '3>./stdlog.txt'.) (stdlog is intended for dev. But can be used by users.) (Use 'stdout', 'stderr', and 'stdnull' to redirect to stdout, stderr, and /dev/null.)
  </pre>

## Example d'utilisation de la bibliothèque 

Voir le fichier [main.c](https://github.com/Romain7426/Calculatrice_decimale/blob/main/src/main.c). 

<pre>
#include "decimal.h" 

void example(void) { 
  uint8_t decimal_env__buffer[DECIMAL_ENV__SIZEOF]; 
  decimal_env_t * decimal_env; 
  decimal_env = decimal_env__make_b(sizeof(decimal_env__buffer), decimal_env__buffer, NULL, stdlog_d); 
  
  decimal_t d;	
  decimal__cast_from_int_r(decimal_env, &d, 43);	
  decimal_t e;	
  decimal__cast_from_int_r(decimal_env, &e, 28);
  decimal__print_r(stdprint_d, decimal_env, &d); write_string(stdprint_d, " + "); decimal__print_r(stdprint_d, decimal_env, &e); write_string(stdprint_d, " = "); 
  decimal__add_r(decimal_env, &d, &e);	
  decimal__print_r(stdprint_d, decimal_env, &d);	
  write_string_ln(stdprint_d, ""); 
}; 
</pre>

<pre>
TODO XXX FIXME 
Ajouter un exemple avec l'analyse d'une expression. 
</pre>


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

Le programme ayant été développé sous [OpenBSD](https://fr.wikipedia.org/wiki/OpenBSD), il devrait fonctionner sous tous les autres [BSD](https://fr.wikipedia.org/wiki/Berkeley_Software_Distribution) et autres systèmes compatibles avec [Unix](https://fr.wikipedia.org/wiki/Unix) (en particulier, il fonctionne sous [MacOSX](https://fr.wikipedia.org/wiki/MacOS)). Sur [Windows](https://fr.wikipedia.org/wiki/Microsoft_Windows), nous ne savons pas, nous n'avons pas essayé, mais le programme devrait pouvoir fonctionner avec [Cygwin](https://fr.wikipedia.org/wiki/Cygwin), [MinGW](https://fr.wikipedia.org/wiki/MinGW), etc.  


## Considérations techniques

L'idée était de pouvoir faire fonctionner la bibliothèque sur un processeur huit bits. Seize bits étant confortables, nous avons utilisés des entiers seize bits ici et là. Ainsi, la bibliothèque devrait fonctionner sans modification sur un processeur seize bits. Pour un processeur huit bits, il n'y a pas de problèmes majeurs, et la bibliothèque devrait pouvoir être amendée pour enlever toutes les références aux entiers seize bits. 

Nous avons fait simple: un nombre décimal est un tableau. Nous avons réservé un octet pour le statut, et le reste pour les chiffres. 

Par défaut, la bibliothèque est en base cent. Mais il est possible de changer cette base: 10, 2, 254, etc. La base minimale est deux. La base maximale est 254. 

La base 254 est celle qui permet de contenir le plus d'information. Toutefois, cette base ne permet pas de représenter les chiffres à virgule en base dix de façon exacte. 
La base 250 est la base la plus grande qui permet de représenter exactement les décimaux en base dix (dans cette base, «0,10» s'écrit «0,25»). 
Une excellente base est la base 240, car elle est multiple de 10, 3, 8, 12, 60. 
Une autre base intéressante est 210, car elle ajoute 7 et donc permet de représenter la fraction «1/7» de façon exacte (en plus de 2, 3, 5, et donc 10). 

La taille du tableau est au maximum de deux cent cinquante six octets (cf. l'hypothèse du processeur huit bits). Par défaut, cette taille est de deux cent cinquante six octets. Cette taille peut être plus petite. Mais elle ne peut pas être plus grande, du fait de notre exigence que la bibliothèque puisse fonctionner sur un processeur huit bits. 

Nous sommes en virgule fixe, c'est-à-dire que le nombre de chiffres dédiés à la partie entière est fixé, et le nombre de chiffre dédié à la partie décimale est fixé. Il est possible de modifier le nombre de chiffre dédié à chaque partie (il faut recompiler). 

Implémenter l'*addition* ne pose aucun problème. 

Implémenter la *soustraction* contient une surprise dans le cas où le second membre est plus grand (la soustraction naturelle est le cas où la première opérande est plus grande que la seconde; l'autre sens est en fait implicitement une équivalence au premier cas: «d - e = -(e - d)»; nous ne nous en rendons pas compte, faisant toutes les étapes intuitivement et automatiquement; si on pose «28 - 80», on obtient une réprésentation complémentaire, que il faut alors re-complémenter pour obtenir la représentation naturelle (ce qui nécessaire dans le cas des entiers longs!) — plus précisément, implicitement, on réalise l'opération suivante: «28 - 80 = [(100+28) - 80] - 100 = -{ 100 - [(100+28) - 80] } »). 

Implémenter la *multiplication* est un peu plus complexe. (Notons que, asymptotiquement, la multiplication est une opération en O(nln(n)), correspondant au fait que la multiplication est une addition dans l'espace des fréquences — la fonction de passage de l'espace temporel à l'espace des fréquences étant en O(nln(n)) — ce qui est porteur de sens si on considère le point de vue de l'information.) 

Le problème commence avec l'implémentation de la *division*. La division est une opération relevant de la virgule flottante. En interne, il faut donc changer de représentation. 
Afin de nous assurer de l'exactitude de l'implémentation de la division, nous avons fait tourner 64k x 64k tests, qui se sont tous révélés positifs. A priori, l'algorithme fonctionne. 
(Notons que, dans l'espace des fréquences, la division est une soustraction. Arrivions-nous à implémenter une fonction efficace pour passer de l'espace temporel à l'espace des fréquences, nous aurions alors une division très efficace. En outre, du point de vue de l'information, on en revient aux considération concernant la multiplication.) 
(Notons aussi que la difficulté supplémentaire comparitivement à la multiplication est de calculer l'inverse. Cela dit, autant calculer directement la division que de la découper en deux étapes, l'algorithme étant le même, et épargne la multiplication post calcul de l'inverse.) 


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

Ce n'est pas extraordinaire, mais cela pourrait être pire. (Le but premier ici est d'avoir quelque chose qui fonctionne.) 

## Futur & TODOs  

Nous travaillons aléatoirement sur les différents projets en cours. Il est tout à fait probable que ce projet n'avance pas au cours des prochaines années, voire décennies. 

Cela ayant été précisé: 
 - Il faut écrire une fonction de conversion depuis une chaîne de caractères. 
   (Pour l'instant, on convertit en [*float*](https://en.wikipedia.org/wiki/Single-precision_floating-point_format), puis dans le format interne. Ceci entraîne justement les arrondis qui nous voulions éviter, et en plus fait dépendre de la librairie [*math*](https://fr.wikipedia.org/wiki/Math.h). Bref. ☹)
 - Pouvoir sélectionner le compilateur [C](https://fr.wikipedia.org/wiki/C_(langage)) en première option (avant la compilation des outils et la configuration, etc.). 
 - Beaucoup de nettoyage et de «[réusinage](https://fr.wikipedia.org/wiki/R%C3%A9usinage_de_code)». 
 - Implémenter les directives («bye»/«quit»/«exit», etc.). 
 - Améliorer la [REPL](https://en.wikipedia.org/wiki/Read%E2%80%93eval%E2%80%93print_loop) afin d'avoir un historique et des raccourcis claviers utilisables. 
 - Implémenter une [GUI](https://fr.wikipedia.org/wiki/Interface_graphique) en [curses](https://fr.wikipedia.org/wiki/Curses). 
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
 - Une [GUI](https://fr.wikipedia.org/wiki/Interface_graphique) de type tableur, comme Excel (parce que c'est très confortable! ☺). 
 - … 
 - Bref, avoir un truc utilisable! 


Merci!! :smile: 

Et nous vous aimons tous. :kissing_heart: 

 

