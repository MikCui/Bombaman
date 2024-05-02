#ifndef _FRAME_
#define _FRAME_

class FRAME;
///Classe FRAME, polymorphisme avec menu, transition et stage
class FRAME
{
	private :

		///la frame va-t-elle etre detruite
		BOOL m_bFinished;

	protected :

		///Constructeur proteger, on peut creer un menu, une transition ou un stage mais pas directement une frame
		inline FRAME() {m_bFinished=false;}

	public :

		///Destructeur de la classe FRAME
		virtual ~FRAME() {}

		///Initialisation
		virtual RESULT Init() {return OK;}
		///Gestion des entrees
		virtual RESULT Input(TOOLS::INPUT* iInput) {return OK;}
		///Animation
		virtual RESULT FrameMove(INT iTimeElapsed) {return OK;}
		///Affichage
		virtual RESULT FrameRender(SDL_Surface* & sScreen) {return OK;}
		///Destruction
		virtual RESULT Destroy() {return OK;}

		///Y aura-t-il une autre frame apres celle la ?
		virtual BOOL NoMoreFrame() {return false;}
		///Si oui donnez la moi
		virtual FRAME* NextFrame() {return NULL;}

		///la frame doit elle etre detruite
		inline BOOL isFinished() {return m_bFinished;}
		///Definir si la frame doit etre detruite
		inline VOID setFinished() {m_bFinished=true;}
};

#endif
