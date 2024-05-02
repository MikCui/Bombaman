#ifndef _TOOLS_
#define _TOOLS_

#define Validate(x)	  {if(FAIL(x)) return x;}
#define Release(x)	   {if(x!=NULL) {delete x; x = NULL;}}
#define ReleaseArray(x)  {if(x!=NULL) {delete[] x; x = NULL;}}

///Namespace TOOLS definissant des outils utiles
namespace TOOLS
{
	typedef void VOID;
	typedef bool BOOL;
	typedef short SHORT;
	typedef int INT;
	typedef unsigned int UINT;
	typedef char CHAR;
	typedef float FLOAT;

	///type de donnees claviers, bouton : non-presse, lache, clique, presse
	typedef enum INPUT
	{
		UNPRESSED = 0,
		RELEASED,
		CLICK,
		PRESSED
	};

	///valeur de retour informant si tout s'est bien deroule ou non
	typedef enum RESULT
	{
		ERROR_SDL = -1,
		OK = 0,
		ERROR = 1
	};

	///tout s'est deroule avec succes ?
	bool SUCCESS(RESULT rResult);
	///il y a eu un echec ?
	bool FAIL(RESULT rResult);

	///classe POINT, definissant un point dans un espace 2D entier
	class POINT
	{
		private :

			///la coordonnee x
			UINT m_uX;
			///la coordonnee y
			UINT m_uY;

		public :

			///Le constructeur n°1 de la classe POINT
			POINT() {}
			///Le constructeur n°2 de la classe POINT
			POINT(UINT x, UINT y) {m_uX = x; m_uY = y;}
			///Obtenir la coordonnee x
			inline UINT getX() {return m_uX;}
			///Obtenir la coordonnee y
			inline UINT getY() {return m_uY;}
			///Definir la coordonnee x
			inline VOID setX(UINT uX) {m_uX=uX;}
			///Definir la coordonnee y
			inline VOID setY(UINT uY) {m_uY=uY;}
			///Definir les coordonnees x et y
			inline VOID setXY(UINT uX, UINT uY) {m_uX=uX;m_uY=uY;}
	};

	///classe POINT, definissant un point dans un espace 2D decimal
	class POINTF
	{
		private :

			///la coordonnee x
			FLOAT m_uX;
			///la coordonnee y
			FLOAT m_uY;

		public :

			///Le constructeur n°1 de la classe POINTF
			POINTF() {}
			///Le constructeur n°2 de la classe POINTF
			POINTF(FLOAT x, FLOAT y) {m_uX = x; m_uY = y;}
			///Obtenir la coordonnee x
			inline FLOAT getX() {return m_uX;}
			///Obtenir la coordonnee y
			inline FLOAT getY() {return m_uY;}
			///Definir la coordonnee x
			inline VOID setX(FLOAT uX) {m_uX=uX;}
			///Definir la coordonnee y
			inline VOID setY(FLOAT uY) {m_uY=uY;}
			///Definir les coordonnees x et y
			inline VOID setXY(FLOAT uX, FLOAT uY) {m_uX=uX;m_uY=uY;}
	};
}

using namespace TOOLS;

#endif

