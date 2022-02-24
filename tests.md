## Tests:

### echo


#### fonctionnels:
- echo bonjour
- echo lalalala lalalalal alalalalal alalalala
- echo lalalala                lalalalal      alalalalal alalalala
- echo loremipsum (lots of random text)
- echo -n
- echo -n bonjour
- echo -n lalalala lalalalal alalalalal alalalala
- echo -n lalalala                lalalalal      alalalalal alalalala
- echo bonjour -n
- echo a '' b '' c '' d
- echo a "" b "" c "" d
- echo -n a '' b '' c '' d
- echo -n a "" b "" c "" d
- echo '' '' ''
- echo $PWD
- echo "$wfjwefielwhfhlwefkhwefwe" a
- echo '$wfjwefielwhfhlwefkhwefwe' a
- echo " \  "
- echo " \" "
- echo " \a "
- echo " \b "
- echo " \! "
- echo " \@ "
- echo " \$ "
- echo " \$LESS "
- echo " \$? "
- echo " \\ "
- echo " \\\ "
- echo " \\\\\ "
- echo ' \  '
- echo ' \" '
- echo ' \a '
- echo ' \b '
- echo ' \! '
- echo ' \@ '
- echo ' \$ ' 
- echo ' $LESS '
- echo ' \$? '
- echo ' \\ '
- echo ' \\\ '




#### non fonctionnels:
- echo -nnnnnnnnnnnnnnnnnnnnn -n -n -n bonjour -n -n
-                       echo                     bonjour             je
-                         echo       -n            bonjour             je
- echo -n -n -n -n bonjour
- echo " \' "
- echo " \| "
- echo " \\\\ "
- echo " \\\\\\ "
- echo " \\\\\\\ "
- echo " \\\\\\\\ "


#### not tested
