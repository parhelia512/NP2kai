#include	"compiler.h"
#include	"inputmng.h"


typedef struct {
	SDL_Scancode	key;
	UINT		bit;
} KEYBIND;

typedef struct {
	UINT	kbs;
	KEYBIND	kb[32];
} INPMNG;

static	INPMNG	inpmng;

static const KEYBIND keybind[] = {
					{SDL_SCANCODE_UP,		NP2_KEY_UP},
					{SDL_SCANCODE_DOWN,		NP2_KEY_DOWN},
					{SDL_SCANCODE_LEFT,		NP2_KEY_LEFT},
					{SDL_SCANCODE_RIGHT,	NP2_KEY_RIGHT},
					{SDL_SCANCODE_RETURN,	KEY_ENTER},
					{SDL_SCANCODE_ESCAPE,	KEY_MENU},
					{SDL_SCANCODE_TAB,		KEY_SKIP}};		/* とりあえずね… */


// ----

void inputmng_init(void) {

	INPMNG	*im;

	im = &inpmng;
	ZeroMemory(im, sizeof(INPMNG));
	im->kbs = sizeof(keybind) / sizeof(KEYBIND);
	CopyMemory(im->kb, keybind, sizeof(keybind));
}

void inputmng_keybind(short key, UINT bit) {

	INPMNG	*im;
	UINT	i;

	im = &inpmng;
	for (i=0; i<im->kbs; i++) {
		if (im->kb[i].key == key) {
			im->kb[i].bit = bit;
			return;
		}
	}
	if (im->kbs < (sizeof(im->kb) / sizeof(KEYBIND))) {
		im->kb[im->kbs].key = key;
		im->kb[im->kbs].bit = bit;
		im->kbs++;
	}
}

UINT inputmng_getkey(short key) {

	INPMNG	*im;
	KEYBIND	*kb;
	UINT	kbs;

	im = &inpmng;
	kb = im->kb;
	kbs = im->kbs;
	while(kbs--) {
		if (kb->key == key) {
			return(kb->bit);
		}
		kb++;
	}
	return(0);
}

