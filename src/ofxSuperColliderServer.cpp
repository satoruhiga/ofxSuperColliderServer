#include "ofxSuperColliderServer.h"

#define NO_LIBSNDFILE
#define SC_DARWIN

#include <sys/stat.h>

#include "SC_DirUtils.h"
#include "SC_World.h"
#include "SC_WorldOptions.h"
#include "SC_Prototypes.h"

struct World *world = NULL;

void ofxSuperColliderServer::init(int port, int samplerate, string plugin_path)
{
	if (world == NULL)
	{
		WorldOptions options;
		
		options = kDefaultWorldOptions;
		options.mPreferredSampleRate = samplerate;
		options.mLoadGraphDefs = true;
		
		string plugins_load_path = ofToDataPath(plugin_path, true);
		
		struct stat fi;
		stat(plugins_load_path.c_str(), &fi);
		
		if (S_ISDIR(fi.st_mode) != 1)
		{
			printf("ERROR: open directory failed '%s'\n", plugins_load_path.c_str());
			return;
		}
		
		options.mUGensPluginPath = plugins_load_path.c_str();
		
		world = World_New(&options);
		
		if (!World_OpenUDP(world, port))
		{
			printf("ERROR: open UDP Port failed '%i'\n", port);
			World_Cleanup(world);
			return;
		}
		
		int err = Group_New(world, 1, &world->mTopGroup);
		if (err)
		{
			printf("ERROR: create default group failed\n");
			return;
		}
	}
}