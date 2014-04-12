@class SBJsonParser;
@class SBJsonWriter;
@class Station;

#import "Pandora/Song.h"


#define PANDORA_API_HOST @"tuner.pandora.com"
#define PANDORA_API_PATH @"/services/json/"
#define PANDORA_API_VERSION @"5"

#define PARTNER_USERNAME @"iphone"
#define PARTNER_PASSWORD @"P2E4FC0EAD3*878N92B2CDp34I0B1@388137C"
#define PARTNER_DEVICEID @"IP01"
#define PARTNER_DECRYPT  "20zE1E47BE57$51"
#define PARTNER_ENCRYPT  "721^26xE22776"

#define INVALID_SYNC_TIME     13
#define INVALID_AUTH_TOKEN    1001
#define INVALID_PARTNER_LOGIN 1002
#define INVALID_USERNAME      1011
#define INVALID_PASSWORD      1012
#define NO_SEEDS_LEFT         1032

typedef void(^SyncCallback)(void);
typedef void(^PandoraCallback)(NSDictionary*);


@interface PandoraRequest : NSObject

/* URL parameters */
@property NSString *method;
@property NSString *authToken;
@property NSString *partnerId;
@property NSString *userId;

/* JSON data */
@property NSMutableDictionary *request;
@property NSMutableData *response;

/* Internal metadata */
@property (copy) PandoraCallback callback;
@property BOOL tls;
@property BOOL encrypted;

@end

/* Wrapper for search results */
@interface SearchResult : NSObject

@property NSString *name;
@property NSString *value;

@end


/* Implementation of Pandora's API */
@interface Pandora : NSObject {
  NSMutableArray *stations;
  int retries;

  NSString *partner_id;
  NSString *partner_auth_token;
  NSString *user_auth_token;
  NSString *user_id;
  uint64_t sync_time;
  uint64_t start_time;
  int64_t syncOffset;
  
  SBJsonParser *json_parser;
  SBJsonWriter *json_writer;
}

@property (readonly) NSArray* stations;

- (BOOL) authenticate:(NSString*)user
             password:(NSString*)password
              request:(PandoraRequest*)req;
- (BOOL) fetchStations;
- (BOOL) getFragment: (Station*)station;
- (BOOL) partnerLogin: (SyncCallback) cb;
- (BOOL) rateSong:(Song*) song as:(BOOL) liked;
- (BOOL) deleteRating:(Song*)song;
- (BOOL) tiredOfSong: (Song*)song;
- (BOOL) search: (NSString*) search;
- (BOOL) createStation: (NSString*) musicId;
- (BOOL) removeStation: (NSString*) stationToken;
- (BOOL) renameStation: (NSString*)stationToken to:(NSString*)name;
- (BOOL) stationInfo: (Station*) station;
- (BOOL) deleteFeedback: (NSString*)feedbackId;
- (BOOL) addSeed: (NSString*)token to:(Station*)station;
- (BOOL) removeSeed: (NSString*)seedId;
- (BOOL) genreStations;
- (void) logout;
- (void) logoutNoNotify;

- (void) applySort:(int)sort;

+ (NSString*) errorString: (int) code;

- (int64_t) time;
- (BOOL) sendRequest: (PandoraRequest*) request;

@end

