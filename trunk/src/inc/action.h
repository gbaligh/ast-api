#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

typedef int astCoreSettingHeaders;

int astGetConfig(char *filename);
int astGetConfigJSON(char *filename);
int astCoreSettings(char *actionid);
int astSipShowPeer(char *peer, char *actionid);
int astSipPeers(char *actionid, message_t *m, int *size);
int astSipShowRegistry(char *actionid, message_t *m, int *size);
int astUpdateConfig(char *filename, int reload, char *category, char *param, char *value, char *action);
int astReload(char *actionid);
int astModuelLoad(char *actionid, char *module, char* loadType);
#endif // ACTION_H_INCLUDED
