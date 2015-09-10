#ifndef SCENE_H
#define SCENE_H
#include "image.h"

using namespace std;

class Scene{

	public:

	int *xcords;

	int *ycords;

	int currentlength = 0;

	Image ** images = NULL;

	Scene (int max);

	~Scene();

	Scene(const Scene & source);

	const Scene & operator=(const Scene & source);

	void changemaxlayers(int newmax);

	void addpicture (const char *FileName, int index, int x, int y);

	void changelayer (int index, int newindex);
	
	void translate (int index, int xcoord, int ycoord);

	void deletepicture (int index);

	Image * getpicture (int index) const;

	Image drawscene () const;


	private:

	void clear();

	void copy(const Scene & other);


};



#endif
