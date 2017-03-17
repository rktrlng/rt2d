/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 */
#include "scene01.h"

Scene01::Scene01()
	: Scene()
{
	t.start();
	st.start();

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(gravity);

	// add a ground plane and walls
	this->setupWorld();
}


Scene01::~Scene01()
{
	removeChild(ge);
	removeChild(lw);
	removeChild(rw);
	delete ge;
	delete lw;
	delete rw;

	delete world;
}

void Scene01::update(float deltaTime)
{
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	if (t.seconds() > timeStep - deltaTime) {
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world->Step(timeStep, velocityIterations, positionIterations);

		// copy position and angle of the bodies to the RT2D Entities.
		int s = bodies.size();
		for (int i = 0; i < s; i++) {
			// get from Box2D
			b2Vec2 position = bodies[i]->GetPosition();
			float32 angle = bodies[i]->GetAngle();

			// apply to RT2D
			entities[i]->position.x = position.x * 100;
			entities[i]->position.y = SHEIGHT - (position.y * 100);
			entities[i]->rotation.z = angle;
		}

		t.start();
	}

	if (st.seconds() > 0.1f) {
		int r = (rand()%100)-50;
		int rx = (SWIDTH/2)+r;
		if (bodies.size() < MAX_BODIES) {
			if (rx%2 == 0) {
				this->addCircleBody(0.32f, (float)rx/100, 10.0f);
			} else {
				this->addBoxBody(32.0f, 32.0f, (float)rx/100, 10.0f);
			}
		}

		st.start();
	}

	if (input()->getKeyUp( KeyCode::Escape )) {
		this->stop();
	}
}

void Scene01::addCircleBody(float radius, float x, float y)
{
	BasicEntity* ce = new BasicEntity();
	ce->position = Point2(x,(SHEIGHT/100)-y)*100;
	Line tmp;
	tmp.createCircle(radius*100, 12);
	tmp.color.r = (rand()%127) + 127;
	tmp.color.g = (rand()%127) + 127;
	tmp.color.b = (rand()%127) + 127;
	ce->addLine(&tmp);
	entities.push_back(ce);
	this->addChild(ce);

	//==========================================================================
	//						Circle Body
	//==========================================================================
	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.angle = 0.5f;
	bodyDef.linearDamping = 0.1f;
	bodyDef.angularDamping = 0.1f;

	b2Body* body = world->CreateBody(&bodyDef);

	// Define circle shape for our dynamic body.
	b2CircleShape dynamicCircle;
	//dynamicCircle.m_p.Set(2.0f, 3.0f);
	dynamicCircle.m_radius = radius;

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicCircle;
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;
	// Override the default friction.
	//fixtureDef.friction = 0.30f;
	//fixtureDef.restitution = 0.30f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// add to both vectors
	bodies.push_back(body);
}

void Scene01::addBoxBody(float hw, float hh, float x, float y)
{
	BasicEntity* be = new BasicEntity();
	be->position = Point2(x,(SHEIGHT/100)-y)*100;
	Line tmp;
	tmp.createBox(hw, hh);
	tmp.color.r = (rand()%127) + 127;
	tmp.color.g = (rand()%127) + 127;
	tmp.color.b = (rand()%127) + 127;
	be->addLine(&tmp);
	entities.push_back(be);
	this->addChild(be);

	//==========================================================================
	//						Square Body
	//==========================================================================
	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.angle = 0.3f;
	bodyDef.linearDamping = 0.1f;
	bodyDef.angularDamping = 0.1f;

	b2Body* body = world->CreateBody(&bodyDef);

	// Define box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(hw/100, hh/100);
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;
	// Override the default friction.
	//fixtureDef.friction = 0.30f;
	//fixtureDef.restitution = 0.30f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// add to both vectors
	bodies.push_back(body);
}

void Scene01::setupWorld()
{
	float worldscale = 100.0f;
	float wallhalfwidth = 25.0f;
	float wallhalfheight = 512.0f;
	float groundwidth = SWIDTH - (wallhalfwidth*2);
	float groundheight = 10.0f;

	// Define the ground body.
	b2BodyDef groundBodyDef;
	float midx = (float) (SWIDTH/2)/worldscale;
	groundBodyDef.position.Set(midx, 0.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(groundwidth/worldscale, groundheight/worldscale);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// ground entity
	ge = new BasicEntity();
	ge->position = Point2(SWIDTH/2, SHEIGHT);
	Line g;
	g.createBox(groundwidth/2, groundheight);
	ge->addLine(&g);
	addChild(ge);

	// =========================================================================
	// Wall L
	// =========================================================================
	// Define the left wall body.
	b2BodyDef wallBodyDefL;
	wallBodyDefL.position.Set(0.0f, 0.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* wallBodyL = world->CreateBody(&wallBodyDefL);

	// Define the ground box shape.
	b2PolygonShape wallBoxL;

	// The extents are the half-widths of the box.
	wallBoxL.SetAsBox(wallhalfwidth/worldscale, wallhalfheight/worldscale);

	// Add the ground fixture to the ground body.
	wallBodyL->CreateFixture(&wallBoxL, 0.0f);

	// left wall entity
	lw = new BasicEntity();
	lw->position = Point2(0, SHEIGHT);
	Line lwl;
	lwl.createBox(wallhalfwidth, wallhalfheight);
	lw->addLine(&lwl);
	addChild(lw);

	// =========================================================================
	// Wall R
	// =========================================================================
	// Define the right wall body.
	b2BodyDef wallBodyDefR;
	float mx = (float) SWIDTH/100;
	wallBodyDefR.position.Set(mx, 0.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* wallBodyR = world->CreateBody(&wallBodyDefR);

	// Define the ground box shape.
	b2PolygonShape wallBoxR;

	// The extents are the half-widths of the box.
	wallBoxR.SetAsBox(wallhalfwidth/worldscale, wallhalfheight/worldscale);

	// Add the ground fixture to the ground body.
	wallBodyR->CreateFixture(&wallBoxR, 0.0f);

	// right wall entity
	rw = new BasicEntity();
	rw->position = Point2(SWIDTH, SHEIGHT);
	Line rwl;
	rwl.createBox(wallhalfwidth, wallhalfheight);
	rw->addLine(&rwl);
	addChild(rw);
}
