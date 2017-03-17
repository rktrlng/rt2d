#include "myscene.h"

MyScene::MyScene() : Scene()
{
	// audio
	Audio::init();
	this->loadSounds();
	sounds[0]->play();

	//square
	square = new MyEntity();
	square->position = Point2(SWIDTH/2, SHEIGHT/2);
	this->addChild(square);

	// text
	for (size_t i = 0; i < 6; i++) {
		Text* t = new Text();
		t->scale = Point(0.25f, 0.25f);
		t->position = Point(50, (i*25)+50);
		text.push_back(t);
		this->addChild(t);
	}
	text[0]->message("Usage: '[' and ']' prev/next music, 'Spacebar' pause music, '1,2,3' effects, 'Q/E' pitch, 'A/D' volume, 'Esc' to quit.");
	text[4]->message("Background Music by PlayOnLoop.com Licensed under Creative Commons By Attribution 4.0");
}


MyScene::~MyScene()
{
	// square
	this->removeChild(square);
	delete square;

	// text
	size_t s = text.size();
	for (size_t i = 0; i < s; i++) {
		this->removeChild(text[i]);
		delete text[i];
	}
	text.clear();

	// sounds
	s = sounds.size();
	for (size_t i = 0; i < s; i++) {
		delete sounds[i];
	}
	sounds.clear();
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( KeyCode::Escape )) {
		this->stop();
	}

	// ###############################################################
	// Handle input
	// ###############################################################
	static int currmusic = 0;
	static float currpitch = 1.0f;
	static float currvolume = 1.5f;

	// music select
	if (input()->getKeyDown( KeyCode::Space )) {
		square->scale = Point(0.5f, 0.5f);
		sounds[currmusic]->pause();
	}
	if (input()->getKeyUp( KeyCode::Space )) {
		square->scale = Point(1.0f, 1.0f);
		sounds[currmusic]->play();
	}

	// sound effects
	if (input()->getKeyDown( KeyCode::Alpha1 )) {
		sounds[3]->play();
	}
	if (input()->getKeyDown( KeyCode::Alpha2 )) {
		sounds[4]->play();
	}
	if (input()->getKeyDown( KeyCode::Alpha3 )) {
		sounds[5]->play();
	}

	// select music
	if (input()->getKeyDown( KeyCode::RightBracket )) {
		sounds[currmusic]->pause();
		currmusic++;
		if (currmusic > 2) { currmusic = 0; }
		sounds[currmusic]->play();
	}
	if (input()->getKeyDown( KeyCode::LeftBracket )) {
		sounds[currmusic]->pause();
		currmusic--;
		if (currmusic < 0) { currmusic = 2; }
		sounds[currmusic]->play();
	}

	// set pitch
	if (input()->getKeyDown( KeyCode::E )) { currpitch += 0.1f; }
	if (input()->getKeyDown( KeyCode::Q )) { currpitch -= 0.1f; }
	sounds[currmusic]->pitch(currpitch);

	std::stringstream sp;
	sp << "Pitch: " << currpitch;
	text[2]->message(sp.str());

	// volume
	if (input()->getKeyDown( KeyCode::A )) { currvolume -= 0.5f; }
	if (input()->getKeyDown( KeyCode::D )) { currvolume += 0.5f; }
	Audio::volume(currvolume);
	std::stringstream sv;
	sv << "Volume: " << currvolume;
	text[3]->message(sv.str());

	// text messages
	if (currmusic == 0) { text[1]->message("Music: 0 POL-fly-hunter-short.wav"); }
	if (currmusic == 1) { text[1]->message("Music: 1 POL-galactic-chase-short.wav"); }
	if (currmusic == 2) { text[1]->message("Music: 2 POL-pyramid-sands-short.wav"); }

	// MS Windows loop fix
	if (sounds[currmusic]->state() == Sound::STATE_STOPPED) {
		sounds[currmusic]->play();
	}
}

void MyScene::loadSounds()
{
	Sound* f = new Sound("assets/POL-fly-hunter-short.wav");
	f->loop(true);
	f->gain(0.5f);
	sounds.push_back(f);

	Sound* g = new Sound("assets/POL-galactic-chase-short.wav");
	g->loop(true);
	g->gain(0.5f);
	sounds.push_back(g);

	Sound* s = new Sound("assets/POL-pyramid-sands-short.wav");
	s->loop(true);
	s->gain(0.5f);
	sounds.push_back(s);

	Sound* p = new Sound("assets/phioo.wav");
	p->gain(1.5f);
	sounds.push_back(p);

	Sound* e = new Sound("assets/explosion.wav");
	e->gain(1.5f);
	sounds.push_back(e);

	Sound* o = new Sound("assets/ooihp.wav");
	o->gain(1.5f);
	sounds.push_back(o);
}
