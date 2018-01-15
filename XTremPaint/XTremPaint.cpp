#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <fstream>
using namespace std;

#include "WindowSDL.h"

#include "SmartPointer.h"
#include "Forme.h"
#include "Ligne.h"
#include "Pixel.h"
#include "Rectangle.h"
#include "ListeBase.h"
#include "Liste.h"
#include "ListeTriee.h"
#include "Iterateur.h"
#include "Dessin.h"
#include "InvalidColorException.h"

void NewDessin();
void OpenDessin();
void SaveDessin();
void CloseDessin();
void AfficheParamDessin();
void ChangeBackground();
void DisplayMemory();
void AddPalette();
void ModifyPalette();
void RemoveColourPalette();
void DisplayColoursPalette();
void importCouleursPalette();
void AjouterForme();
void RemoveForme();
void ChangeColourForme();
void AfficheCarractForme();
void importFormes();

Dessin *dessin;
Forme *forme;
WindowSDLclick click1, click2;

int main()
{
	bool end = false;
	int choix = -1;
	
	pasfini:;
	do
	{
		system("clear");
		cout << "****************************** XTremPaint ******************************" << endl;
		cout << "Gestion des Fichiers" << endl;
		cout << "\t1. Nouveau Dessin" << endl;
		cout << "\t2. Ouvrir Dessin" << endl;
		cout << "\t3. Enregistrer Dessin" << endl;
		cout << "\t4. Fermer Dessin" << endl;
		cout << "Gestion générale" << endl;
		cout << "\t5. Afficher les paramètres du dessin (Taille + Couleur de fond)" << endl;
		cout << "\t6. Spécifier une couleur de fond" << endl;
		cout << "\t7. Afficher l’état de la mémoire" << endl;
		cout << "Gestion de la palette de couleurs" << endl;
		cout << "\t8. Ajouter une couleur" << endl;
		cout << "\t9. Modifier une couleur" << endl;
		cout << "\t10. Supprimer une couleur" << endl;
		cout << "\t11. Afficher toutes les couleurs de la palette" << endl;
		cout << "\t12. Importer une palette de couleurs à partir d’un fichier csv" << endl;
		cout << "Gestion des formes géométriques" << endl;
		cout << "\t13. Ajouter une forme" << endl;
		cout << "\t14. Supprimer une forme" << endl;
		cout << "\t15. Modifier la couleur d’une forme" << endl;
		cout << "\t16. Afficher les infos de toutes les formes" << endl;
		cout << "\t17. Importer un ensemble de formes à partir d’un fichier csv" << endl;
		cout << "\t0. Quitter" << endl;
		cout << "--> ";
		
		cin >> choix;
		
		switch(choix)
		{
			case 0: end = true;
				break;
			case 1: NewDessin();
				break;
			case 2: OpenDessin(); 
				break;
			case 3: SaveDessin(); // Pointeur this erroné lors du passage dans les méthodes Save -> ça merde
				break;
			case 4: CloseDessin();
				break;
			case 5: AfficheParamDessin();
				break;
			case 6: ChangeBackground();
				break;
			case 7: DisplayMemory();
				break;
			case 8: AddPalette();
				break;
			case 9: ModifyPalette();
				break;
			case 10: RemoveColourPalette();
				break;
			case 11: DisplayColoursPalette();
				break;
			case 12: importCouleursPalette();
				break;
			case 13: AjouterForme();
				break;
			case 14: RemoveForme();
				break;
			case 15: ChangeColourForme();
				break;
			case 16: AfficheCarractForme();
				break;
			case 17: importFormes();
				break;
			default: cerr << "Saisie incorrecte !" << endl;
				 sleep(2);
				 break;
		}
	}
	while(!end);
	
	if(dessin != NULL)
	{
		CloseDessin();
		if(dessin != NULL)
		{
			end = 0;
			goto pasfini;
		}
	}
	
	cout << "Développeur: Capitano Jonathan" << endl;
	cout << "Bye !! ;)" << endl;
	
	return 0;
}


void NewDessin()
{
	int sizex, sizey;
	
	if(dessin)
		delete dessin;
	
	dessin = new Dessin();	
	
	dessin->importCouleurs("couleurs.csv");
	
	system("clear");
	cout << "Choisissez la taille de la fenêtre:" << endl;
	cout << "Largeur = ";
	cin >> sizex;
	dessin->setLargeur(sizex);
	cout << "Hauteur = ";
	cin >> sizey;
	dessin->setHauteur(sizey);
	
	try
	{
		WindowSDL::open(dessin->getLargeur(), dessin->getHauteur());
		ChangeBackground();
	}
	catch(WindowSDLexception arg)
	{
		cerr << arg.getMessage() << endl;
		delete dessin;
		sleep(2);
		return;
	}
	
	
	
	
}

void OpenDessin()
{
	char filename[150];
	cout << "Veuillez indiquer le nom du dessin: ";
	cin >> filename;
	ifstream fichier(filename, ios::in);
	
	if(fichier)
	{
		
		if(dessin == NULL)
		{
			dessin = new Dessin();
			
			dessin->Load(fichier);
			try
			{
				WindowSDL::open(dessin->getLargeur(), dessin->getHauteur());
				WindowSDL::setBackground(dessin->getBackground().getRouge(), dessin->getBackground().getVert(), dessin->getBackground().getBleu());
			}
			catch(WindowSDLexception arg)
			{
				cerr << arg.getMessage() << endl;
				delete dessin;
				sleep(2);
				return;
			}
			
			/*for(int i = 0; i < dessin->getFormes().getNombreElements(); i+=1)
			{
				dessin->getFormes().getElement(i)->valeur->Dessine();
			}*/
			
		}
		else
		{
			cerr << "Un dessin est déjà ouvert" << endl;
			sleep(2);
		}
		
		fichier.close();
		
		
	}
}

void SaveDessin()
{
	char choix;
	char filename[150];
	
	system("clear");
	if(dessin == NULL)
	{
		cerr << "Aucun dessin ouvert !" << endl;
		sleep(2);
		return;
	}
	
	cout << "Veuillez indiquer le nom du dessin: ";
	cin >> filename;
	ofstream fichier(filename, ios::out);
	
	if(fichier)
	{
		
		do
		{
			cout << "Voulez-vous écraser le fichier: " << filename << " si existant ? (y/n)" << endl;
			cin >> choix;
		}
		while(choix != 'y' && choix != 'n');
		if(choix == 'n')
		{
			cout << "Le dessin n'a pas été sauvé !" << endl;
			sleep(2);
			return;
		}
		if(dessin != NULL)
		{
			dessin->Save(fichier);
		}
	}
}

void CloseDessin()
{
	char save;
	
	if(dessin != NULL)
	{
		system("clear");
		cout << "Souhaitez vous sauver avant de quitter? (y/n/a)" << endl << endl;
		cout << "--> ";
		cin >> save;
		if(save == 'y')
		{
			SaveDessin();
			delete dessin;
			dessin = NULL;
			WindowSDL::close();
		}
		else if(save == 'a')
		{
			return;
		}
		else if(save == 'n')
		{
			delete dessin;
			dessin = NULL;
			WindowSDL::close();
			system("clear");
			cout << "Le dessin n'a pas été sauvé.." << endl;
			sleep(2);
		}
	
	
		
	}
}

void AfficheParamDessin()
{
	char end;
	system("clear");
	if(dessin != NULL)
	{
		cout << "******** Paramètres du Dessin ********" << endl << endl;
		cout << "Largeur: " << dessin->getLargeur() << " px" << endl;
		cout << "Hauteur: " << dessin->getHauteur() << " px" << endl;
		cout << "Background: " << dessin->getBackground() << endl << endl;
		cout << "Entrez quelque chose pour continuer.." << endl;
		cin >> end;
	}
	else
	{
		cerr << "Aucun dessin ouvert.. Ouvrez en un avant !" << endl;
		sleep(2);
	}
	
}


void ChangeBackground()
{
	system("clear");
	
	if(dessin == NULL)
	{
		cerr << "Aucun dessin ouvert !" << endl;
		sleep(2);
		return;
	}
	
	cout << "*** Couleurs disponnibles ***" << endl;
	dessin->getPalette().Affiche();
	
	char couleur[50];
	Couleur *tempCouleur;
	do
	{
		cout << "Entrez la couleur de fond: ";
		cin >> couleur;
		tempCouleur = dessin->getCouleurPalette(couleur);
	}
	while(tempCouleur == NULL);
	
	dessin->setBackground(*tempCouleur);
	
	WindowSDL::setBackground(dessin->getBackground().getRouge(), dessin->getBackground().getVert(), dessin->getBackground().getBleu());
	
	for(int i = 0; i < dessin->getFormes().getNombreElements(); i+=1)
	{
		dessin->getFormes().getElement(i)->valeur->Dessine();
	}
}

void DisplayMemory()
{
	char end;
	system("clear");
	cout << "******** Etat de la mémoire ********" << endl << endl;
	cout << "Nombre total d'objets instanciés: " << (Forme::getCompteur() + Couleur::getCompteur() + Point::getCompteur()) << " objets" << endl;
	cout << "Nombre de Points: " << Point::getCompteur() << " objets" << endl;
	cout << "Nombre de Couleurs: " << Couleur::getCompteur() << " objets" << endl;
	cout << "Nombre de Formes: " << Forme::getCompteur() << " objets" << endl << endl;
	cout << "Entrez quelque chose pour continuer.." << endl;
	cin >> end;
}

void AddPalette()
{
	int r, v, b;
	char NomCouleur[100];
	
	system("clear");
	
	if(dessin == NULL)
	{
		cerr << "Aucun dessin ouvert !" << endl;
		sleep(2);
		return;
	}
	
	system("clear");
	cout << "Nom de la couleur à ajouter à la palette: ";
	cin >> NomCouleur;
	cout << "Paramétrage de " << NomCouleur << endl << endl;
	cout << "Rouge: ";
	cin >> r;
	cout << "Vert: ";
	cin >> v;
	cout << "Bleu: ";
	cin >> b;
	
	try
	{
		Couleur temp(r, v, b, NomCouleur);
		dessin->AjouteCouleur(temp);
	}
	catch(InvalidColorException arg)
	{
		cerr << arg.getMessage() << endl;
		sleep(2);
	}
}

void ModifyPalette()
{
	Couleur* changeColour;
	int r, v, b;
	char NomCouleur[100];
	
	system("clear");
		
	if(dessin == NULL)
	{
		cerr << "Aucun dessin ouvert !" << endl;
		sleep(2);
		return;
	}
	
	if(dessin->getPalette().getNombreElements() == 0)
	{
		cerr << "Aucune Couleur n'est disponnible dans la palette !" << endl;
		sleep(2);
		return;
	}
	
	cout << "Nom de la couleur à modifier dans la palette: ";
	cin >> NomCouleur;
	changeColour = dessin->getCouleurPalette(NomCouleur);
	
	if(changeColour == NULL)
	{
		cerr << "Aucune couleur nommée " << changeColour << " n'a été trouvée dans la palette";
	}
	
	cout << "Nouveau nom de la couleur: ";
	cin >> NomCouleur;
	
	cout << "Paramétrage de " << NomCouleur << endl << endl;
	cout << "Rouge: ";
	cin >> r;
	cout << "Vert: ";
	cin >> v;
	cout << "Bleu: ";
	cin >> b;
	try
	{
		changeColour->setNom(NomCouleur);
		changeColour->setRouge(r);
		changeColour->setVert(v);
		changeColour->setBleu(b);
		dessin->ReplaceCouleurPalette(NomCouleur, *changeColour);
	}
	catch(InvalidColorException arg)
	{
		cerr << arg.getMessage() << endl;
		sleep(2);
	}
	
}

void RemoveColourPalette()
{
	char recherche[25];
	
	system("clear");
	
	
	if(dessin == NULL)
	{
		cerr << "Aucun dessin ouvert !" << endl;
		sleep(2);
		return;
	}
	
	if(dessin->getPalette().getNombreElements() == 0)
	{
		cerr << "Aucune Couleur n'est disponnible dans la palette !" << endl;
		sleep(2);
		return;
	}
	
	cout << "Couleurs disponnibles: " << endl << endl;
	dessin->getPalette().Affiche();
	cout << endl << "Entrez le nom de la couleur à supprimer: ";
	cin >> recherche;
	
	Liste<Couleur> des(dessin->getPalette());
	Iterateur<Couleur> itcoul(des);
	itcoul.reset();
	while(strcmp(recherche, (*(&itcoul)).getNom()) != 0 && !itcoul.end())
	{
		itcoul++;
	}
	if(!itcoul.end())
	{
		cout << "Supprimé avec succès !" << endl;
		itcoul.remove();
	}
	else
	{
		if(strcmp(recherche, (*(&itcoul)).getNom()) == 0)
		{
			cout << "Supprimé avec succès !" << endl;
			itcoul.remove();
		}
		else
		{
			cout << "Element introuvable !" << endl;
		}
	}
	dessin->setPalette(des);
	sleep(2);
}

void DisplayColoursPalette()
{
	char end;
	
	system("clear");
	
	if(dessin != NULL)
	{
		cout << "*** Couleurs de la palette ***" << endl << endl;
		dessin->getPalette().Affiche();
		cout << endl << "Entrez quelque chose pour continuer.." << endl;
		cin >> end;
	}
	else
	{
		cerr << "Aucun dessin ouvert !" << endl;
		sleep(2);
		return;
	}
}

void importCouleursPalette()
{
	system("clear");
	
	if(dessin != NULL)
	{
		char filename[150];
		cout << "Veuillez indiquer le nom du fichier csv de couleurs à importer: ";
		cin >> filename;
		
		dessin->importCouleurs(filename);
	}
	else
	{
		cerr << "Aucun dessin ouvert !" << endl;
		sleep(2);
		return;
	}
}

void AjouterForme()
{
	int choix = -1;
	char rempli;
	char ColourName[100];
	char buff[20];
	Couleur *SelectedColour;
	Point p1, p2;
	
	if(dessin != NULL)
	{
		try
		{
			do
			{
				system("clear");
				cout << "Que voulez-vous dessiner?" << endl;
				cout << "1. un pixel" << endl;
				cout << "2. une ligne" << endl;
				cout << "3. un rectangle" << endl;
				cout << "0. Revenir au menu principal" << endl << endl;
				cout << "--> ";
				cin >> choix;
				
				if(choix > 3 || choix < 1)
				{
					goto end;
				}
				
				if(choix == 3)
				{
					do
					{
						cout << "Un rectangle rempli? (y/n)" << endl;
						cin >> rempli;
					}
					while(rempli != 'y' && rempli != 'n');
					
				}
				
				do
				{
					system("clear");
					cout << "Couleurs disponnibles: " << endl << endl;
					dessin->getPalette().Affiche();
					cout << "Entrez la couleur souhaitée: ";
					cin >> ColourName;
					
					SelectedColour = dessin->getCouleurPalette(ColourName);
					
					if(SelectedColour == NULL)
					{
						cerr << "La couleur n'est pas dans la palette" << endl;
					}
				}
				while(SelectedColour == NULL);
				
				system("clear");
				cout << "Dessinez sur l'interface graphique..." << endl;
				
				click1 = WindowSDL::waitClick();
				
				p1.setX(click1.getX());
				p1.setY(click1.getY());
				
				
				cout << "Vous avez clique en (" << click1.getX() << "," << click1.getY() << ")" << endl;
			    	
			    	if(choix != 1)
			    	{
			    		click2 = WindowSDL::waitClick();
				    	
				    	p2.setX(click2.getX());
					p2.setY(click2.getY());
					
					
				    	switch(choix)
				    	{
				    		case 2: forme = new Ligne();
				    			sprintf(buff, "L%d", Forme::getCompteur());
				    			((Ligne*)forme)->setId(buff);
				    			((Ligne*)forme)->setExtremite(p2);
				    			break;
				    		case 3: forme = new Rectangle();
				    			sprintf(buff, "R%d", Forme::getCompteur());
				    			((Rectangle*)forme)->setId(buff);
				    			if(rempli == 'y')
				    			{
				    				((Rectangle*)forme)->setRempli(1);
				    			}
				    			else
				    			{
				    				((Rectangle*)forme)->setRempli(0);
				    			}
				    			((Rectangle*)forme)->setDimX(p2.getX());
				    			((Rectangle*)forme)->setDimY(p2.getY());
				    			break;
				    	}
				    	
				    	
				    	forme->setPosition(p1);
				    	forme->setCouleur(SelectedColour);
				    	forme->setProfondeur(forme->getProfondeur() + forme->getCompteur());
				    	
				    	
				}
				else
				{
					forme = new Pixel();
					
					sprintf(buff, "P%d", Forme::getCompteur());
					((Pixel*)forme)->setId(buff);
					forme->setPosition(p1);
					forme->setCouleur(SelectedColour);
					
				}
				
				forme->Dessine();
				
				dessin->AjouteForme(forme, SelectedColour->getNom());
				
				end:;
		    	}
		    	while(choix != 0);
	    	}
	    	catch(WindowSDLexception arg)
		{
			cerr << arg.getMessage() << endl;
			sleep(2);
			return;
		}
	}
	else
	{
		system("clear");
		cerr << "Aucun dessin ouvert !" << endl;
		sleep(2);
		return;
	}

}

void RemoveForme()
{
	char recherche[25];
	
	system("clear");
	
	if(dessin == NULL)
	{
		cerr << "Aucun dessin ouvert !" << endl;
		sleep(2);
		return;
	}
	
	if(dessin->getFormes().getNombreElements() == 0)
	{
		cerr << "Aucune forme n'est disponnible !" << endl;
		sleep(2);
		return;
	}
	
	cout << "Formes disponnibles: " << endl << endl;
	dessin->getFormes().Affiche();
	cout << endl << "Entrez l'id de la forme à supprimer: ";
	cin >> recherche;
	
	ListeTriee<SmartPointer<Forme> > des(dessin->getFormes());
	Iterateur<SmartPointer<Forme> > itcoul(des);
	itcoul.reset();
	while(strcmp(recherche, (*(&itcoul))->getId()) != 0 && !itcoul.end())
	{
		itcoul++;
	}
	if(!itcoul.end())
	{
		cout << "Supprimé avec succès !" << endl;
		itcoul.remove();
	}
	else
	{
		if(strcmp(recherche, (*(&itcoul))->getId()) == 0)
		{
			cout << "Supprimé avec succès !" << endl;
			itcoul.remove();
		}
		else
		{
			cout << "Element introuvable !" << endl;
		}
	}
	
	dessin->setFormes(des);
}

void ChangeColourForme()
{
	char recherche[25];
	char ColourName[25];
	Couleur *SelectedColour;
	
	system("clear");
	if(dessin == NULL)
	{
		cerr << "Aucun dessin ouvert !" << endl;
		sleep(2);
		return;
	}
	
	if(dessin->getFormes().getNombreElements() == 0)
	{
		cerr << "Aucune forme n'est disponnible !" << endl;
		sleep(2);
		return;
	}
	
	if(dessin->getPalette().getNombreElements() == 0)
	{
		cerr << "Aucune Couleur n'est disponnible dans la palette !" << endl;
		sleep(2);
		return;
	}
	
	cout << "Formes disponnibles: " << endl << endl;
	dessin->getFormes().Affiche();
	cout << endl << "Entrez l'id de la forme à modifier la couleur: ";
	cin >> recherche;
	system("clear");
	cout << "Couleurs disponnibles: " << endl << endl;
	dessin->getPalette().Affiche();
	cout << "Sélectionnez la couleur pour la forme " << recherche << ": ";
	cin >> ColourName;
	SelectedColour = dessin->getCouleurPalette(ColourName);
	
	/*for(int i = 0; i < dessin->getFormes().getNombreElements(); i+=1)
	{
		if(dessin->getFormes().getElement(i)->valeur->getId() != NULL)
		{
			cerr << dessin->getFormes().getElement(i)->valeur->getId() << endl;
			if(strcmp(recherche, dessin->getFormes().getElement(i)->valeur->getId()) == 0)
			{
				//dessin->getFormes().getElement(i)->valeur->setCouleur(SelectedColour); // Refuse car setCouleur pas const..
				goto end;
			}
		}
	}*/
	
	
	ListeTriee<SmartPointer<Forme> > des(dessin->getFormes());
	Iterateur<SmartPointer<Forme> > itcoul(des);
	itcoul.reset();
	while(strcmp(recherche, (*(&itcoul))->getId()) != 0 && !itcoul.end())
	{
		itcoul++;
	}
	
	if(strcmp(recherche, (*(&itcoul))->getId()) == 0)
	{
		(*(&itcoul))->setCouleur(SelectedColour); // Refuse car setCouleur pas const..
		(*(&itcoul))->Dessine();
		goto end;
	}
	
	cerr << "La forme " << recherche << " n'a pas été trouvée!" << endl;
	sleep(2);
	return;
	end:;
	cout << "Couleur modifiée !" << endl;
	sleep(2);
}

void AfficheCarractForme()
{
	char recherche[25];
	
	system("clear");
	
	if(dessin == NULL)
	{
		cerr << "Aucun dessin ouvert !" << endl;
		sleep(2);
		return;
	}
	
	if(dessin->getFormes().getNombreElements() == 0)
	{
		cerr << "Aucune forme n'est disponnible !" << endl;
		sleep(2);
		return;
	}
	
	cout << "Formes disponnibles: " << endl << endl;
	dessin->getFormes().Affiche();
	cout << endl << "Entrez l'id de la forme à rechercher: ";
	cin >> recherche;
	
	ListeTriee<SmartPointer<Forme> > des(dessin->getFormes());
	Iterateur<SmartPointer<Forme> > itcoul(des);
	itcoul.reset();
	while(strcmp(recherche, (*(&itcoul))->getId()) != 0 && !itcoul.end())
	{
		itcoul++;
	}
	
	if(strcmp(recherche, (*(&itcoul))->getId()) == 0)
	{
		char endc;
		system("clear");
		cout << "*** Infos sur la forme " << (*(&itcoul))->getId() << " ***" << endl << endl;
		
		cout << (*(&itcoul))->getInfos() << endl << endl;
		
		cout << "Entrez quelque chose pour continuer.." << endl;
		cin >> endc;
		goto end;
	}
	cerr << "La forme " << recherche << " n'a pas été trouvée!" << endl;
	sleep(2);
	return;
	end:;
}

void importFormes()
{
	char filename[50];
	int choix = -1;
	
	system("clear");
	
	if(dessin != NULL)
	{
		do
		{
			system("clear");
			cout << "Quel type de fichier importer?" << endl;
			cout << "1. Pixels" << endl;
			cout << "2. Lignes" << endl;
			cout << "3. Rectangles" << endl;
			cout << "0. Revenir au menu principal" << endl << endl;
			cout << "--> ";
			cin >> choix;
		}
		while(choix < 0 && choix > 3);
		
		cout << "Nom du fichier à importer: ";
		cin >> filename;
		
		switch(choix)
		{
			case 1: dessin->importPixels(filename);
				break;
			case 2: dessin->importLignes(filename);
				break;
			case 3: dessin->importRectangles(filename);
				break;
		}
		
		for(int i = 0; i < dessin->getFormes().getNombreElements(); i+=1)
		{
			dessin->getFormes().getElement(i)->valeur->Dessine();
		}
		
	}
	else
	{
		cerr << "Aucun dessin ouvert !" << endl;
		sleep(2);
		return;
	}
}
