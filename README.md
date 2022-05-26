# Blackbox
Nelson Alvares Cedeno B90368 | Andrea Alvarado Acon B90272 | Greivin Sanchez Garita B97248

## Diseno e implementacion 
- En este [enlace](https://www.figma.com/file/zDZ1Bhmu9HOFat2fO6UKPz/Blackbox?node-id=0%3A1) encontrará el diseño web del sistema.
- En este [enlace](https://lucid.app/lucidchart/a4a755fa-cfc7-4c17-8df8-3b907f9f6151/edit?viewport_loc=-1080%2C-2122%2C2994%2C1445%2CmKIcKVMLJDIf&invitationId=inv_6fdc49b8-078a-4ec1-aff7-0a6a5915fc1f#) usted puede encontrar el diseño de la base de datos utilizado.

### Arquitectura del proyecto: 
- En la carpeta del repositorio encontrará las siguientes carpetas:
    - Carpeta HTML: esta contiene los archivos estructurados que se mostraran en la web. Así como la carpeta componentes que contiene código reutilizable para los mismos html.
    - Carpeta misc: contiene un archivo de configuración para apache que se indicará cómo usar más adelante. 
    - Carpeta obj: archivos con extensión .o para ser linkeados en el proyecto. No es necesario modificar nada el mismo make se encargará de esto.
    - Carpeta src: es la parte fuerte dle proyecto. Aquí encontrará el código fuente que da vida al proyecto. 
        - src/core: estos son los archivos .c que generan los .cgi ejecutados desde el navegador.
        - src/db: librerías y archivos necesarios para la correcta comunicación con la base de datos. 
        - src/domain: estructuras de las entidades del negocio. Ej: user, products, cart, credit_card. 
        - src/html: archivos ncesarios para la interpretación de componentes en html.
        - src/http: archivos necesarios para la comunicación con el protocolo http y apache. 
        - src/mem: estructuras de datos.Ej: listas, árboles. 
        - src/utils: archivos con funciones útiles. Ej: generar token de sesión, manejo de expresiones regulares, entre otros. 
    - WWW: archivos complementarios para los html. 
        - www/css
        - www/images

## Indicaciones apropiadas para la instalacion
- Requerimientos:
    - Apache Server 
    - MySQL 
    - Compilador de lenguaje C

- Indicaciones: 
    1. Antes de comenzar verifique que cuenta con todos los requerimientos establecidos.
    2. Si cuenta con permisos puede exportar el repositorio desde este [enlace.](https://github.com/N3L-s0n/blackbox.git)
    3. Esto generará una carpeta con todos los archivos necesarios para la instalación.
    4. Copie el archivo que se encuentra en **blackbox/src/misc** en **/etc/apache/sites-available/** esto para configurar los permisos de acceso de directorios en apache.
    5. Elimine el archivo que se encuentra en **/etc/apache2/sites-enabled/** y ejecute el comando: **ln -s ../sites-available/001-blackbox.conf.** Esto habilitará la configuracion que hemos establecido en el paso anterior.
    6. Habilite que apache pueda ejecutar archivos cgi:  **sudo ln -s /etc/apache2/mods-available/cgi.load**
    7. Recargue el servicio de apache: **sudo service apache2 reload**
    8. Ejecute los siguientes comandos para crear las carpetas donde se alojaran los archivos del sitio:  **sudo mkdir /var/www/blackbox** seguido de **sudo chown usuario:usuario /var/www/blackbox** y asegurese de reemplazar su usuario en el ultimo comando. 
    9. Ejecute el archivo make (*make page=página*) para cada una de las siguientes páginas:
        * register
        * login
        * cart 
        * index
        * addProduct
        * products
        * questions
    10. Disfrute de la aplicación ingresando a su navegador y probando a entrar a localhost.