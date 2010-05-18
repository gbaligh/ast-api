/* $Id: event.h,v 1.3 2010/05/10 15:50:34 bguesmi Exp $ */
#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED


#define ASTMAN_EVENT_PEER_ENTRY             "PeerEntry"
#define ASTMAN_EVENT_PEER_LIST_COMPLETE     "PeerlistComplete"
#define ASTMAN_EVENT_REGISTRATIONS_COMPLETE "RegistrationsComplete"
#define ASTMAN_EVENT_REGISTRY_ENTRY          "RegistryEntry"

ASTMAN_EVENT_CALLBACK astEventGetDefaultCallback();

int SipShowRegistryCallBack(struct mansession *s, struct message *m);
int CoreShowChannelsCallBack(struct mansession *s, struct message *m);
int SipPeersCallBack(struct mansession *s, struct message *m);


#endif // EVENT_H_INCLUDED
