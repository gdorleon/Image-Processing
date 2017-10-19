/*  Cours de Traitement d'images
      TP1  - 1ere Partie
      Programme de Calcul du Profil d'Intensité d'une Image  	         	
      Etudiant: Ginel DORLEON - P20- IFI 2016  

    Purpose of this program ?
     
     This program makes it possible to obtain the
     Intensity of an image along a line or a selected column.  																                                     
     How to execute ? 																						////
      In the command line, while in the main directory, type:
       1- cmake
     then       												 		
      2- make
      3- ./ProfIntensiteLigne image_name profile_type (line or rows) index number	
																							////
			 
*/

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;




// Ici, dans les lignes suivantes, nous écrivons la fonction principale qui va dessiner la ligne sur l'image

void drawLine(Mat image, char* type, int nb_ligne){

	Point markStart, mark_end;

	if (strcasecmp(type,"Line")==0){

		markStart.x = 0;
		markStart.y = nb_ligne;
		mark_end.x = image.cols;
		mark_end.y = nb_ligne;
	}
	else if(strcasecmp(type,"Rows")==0){
		markStart.x = nb_ligne;
		markStart.y = 0;
		mark_end.x = nb_ligne;
		mark_end.y = image.rows;
	}

//Dessiner la ligne sur l'image
	line(image, markStart, mark_end, Scalar(0, 0, 255), 1, 8);

// Affichage de l'image ici avec la fonction imshow

	imshow("Your image",image);

	
	if(!imwrite("new_image.png", image)) // Sauvegarder l'image comme decrit dans les consignes
 cout<<""<<endl;
}


//  Ici nous ecrivons la fonction qui va nous permettre de determiner le profil de l'image

void ProfileIntensity(Mat image, char* type, int nb_ligne)
{
   
// Profile d'Intensity  pour une ligne horizontale
        int curved_window;  
	if(strcasecmp(type,"Line")==0){
		curved_window = image.cols;
	}
	else if(strcasecmp(type,"Rows")==0){
		curved_window = image.rows;
	}
//Profile de notre image	

		Mat img_profil (256,curved_window,CV_8UC3,Scalar(0,0,0));

		for(int i = 0; i < curved_window-1; i++)
		{   

//Recuperer les valeurs de pixel
                       Vec3b start_pixel; // Value of the begining of the pixel
                       Vec3b end_pixel;  // Valeur de fin du pixel
			if(strcasecmp(type,"Line")==0){
		    start_pixel  = image.at<Vec3b>(nb_ligne, i);
		    end_pixel = image.at<Vec3b>(nb_ligne,i+1);
			}
			else if(strcasecmp(type,"Rows")==0){
			start_pixel  = image.at<Vec3b>(i, nb_ligne);
			end_pixel = image.at<Vec3b>(i+1,nb_ligne);
			}
// Boucle qui gere les niveauc de gris et les couleurs basiques 
                        Point first_mark, second_mark;   // Variable pour tracer le trait de profil
			for(int j = 0; j < 3; j++)
			{
				first_mark.x = i;
				second_mark.x = i+1;
				first_mark.y = 255 - start_pixel.val[j];
				second_mark.y = 255 - end_pixel.val[j];
// Ces 3 lignes representent des aspects dans notre code, elles sont usuelles, elles ne changeront pas
                  if(j==0) line(img_profil, first_mark, second_mark, Scalar(255, 0, 0), 1, 8); // la ligne de couleur BLEU
                  if(j==1) line(img_profil, first_mark, second_mark, Scalar(0, 255, 0), 1, 8); // La ligne de couleur ROUGE
		  if(j==2) line(img_profil, first_mark, second_mark, Scalar(0, 0, 255), 1, 8); // Ligne pour la couleur VERT
			}

		}
		imshow( "Profile", img_profil );

// Ici, nous sauvons l'image du profil d'intensite dans le dossier courant
if(!imwrite("Intensity_Profile.png", img_profil)) // S'il la sauvegarde echoue
cout<<"err"<<endl;
	}





// Main Function

  int main( int argc, char** argv )
{

// Load our image from img_set
        Mat img_set; // Store our image here
	img_set = imread( argv[1], 1 ); 

// TEst sur la saisie de nos parametres , line format, row format, image name format and syntaxe
	if( argc != 4 )
	{
	cout << "Format Incorrect: filename image_name profile_type nb_line_line or column"<<endl;
	}
	else
	{
	if(!img_set.data){
	cout<<"Image not found"<<endl;
	return 0;
		}
	else
		{
	if((strcasecmp(argv[2],"Line")==0)||(strcasecmp(argv[2],"Rows")==0))
			{
	
// Test sur le nombre de ligne
        int check=0;
        int nb_ligne; // nb_line de la colonne ou ligne de l'index donne
	nb_ligne = atoi(argv[3]);
        if((strcasecmp(argv[2],"Line")==0)&&(img_set.rows < nb_ligne)){
	cout<<" choose a smaller"<<endl;
        check =1;
}
// Test sur le nombre de colonne				
	else if((strcasecmp(argv[2],"Rows")==0)&&(img_set.cols < nb_ligne)){
	 cout <<"column must be < to img size"<<endl;
	 check = 1;
	}
// Maintenant, si tout se passe bien ok, i-e test= 0
	if(check==0)
	{
	//Nous pouvons dessiner notre ligne
	ProfileIntensity(img_set, argv[2],nb_ligne);
 // Et dessinner sur l'image
	drawLine(img_set, argv[2],nb_ligne);
        waitKey(0);
        cvDestroyAllWindows();
        return 0;	
        }}
 
}
}
}
