#include "ofxSuperColliderServer.h"

#define NO_LIBSNDFILE
#define SC_DARWIN

#include <sys/stat.h>

#include "SC_DirUtils.h"
#include "SC_World.h"
#include "SC_WorldOptions.h"
#include "SC_Prototypes.h"
#include "SC_GraphDef.h"

struct World *world = NULL;

void ofxSuperColliderServer::init(int port, int samplerate, string synthdef_dir)
{
	if (world == NULL)
	{
		WorldOptions options;
		struct stat fi;
		
		options = kDefaultWorldOptions;
		options.mPreferredSampleRate = samplerate;
		options.mLoadGraphDefs = true;
		// options.mVerbosity = 1;
		
		//
		// setup synthdef dir
		//
		
		synthdef_dir = ofToDataPath(synthdef_dir, true);
		
		char resourceDir[1024];
		sc_GetUserAppSupportDirectory(resourceDir, MAXPATHLEN);
		sc_AppendToPath(resourceDir, "synthdefs");
		
		synthdef_dir += string(":") + string(resourceDir);
		setenv("SC_SYNTHDEF_PATH", synthdef_dir.c_str(), 1);
		
		//
		// setup supercollider server
		//
		
		world = World_New(&options);
		
		if (!World_OpenUDP(world, port))
		{
			ofLog(OF_LOG_ERROR, "open UDP Port failed '%i'\n", port);
			World_Cleanup(world);
			return;
		}
		
		int err = Group_New(world, 1, &world->mTopGroup);
		if (err)
		{
			ofLog(OF_LOG_ERROR, "create default group failed\n");
			return;
		}
	}
}