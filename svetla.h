enum HeadlightsMode {
  VYPNUTO,
  OBRYSOVA,
  POTKAVACI,
  DALKOVA,
  HOUKACKA
};

void controlLights();
void setupLights();

extern HeadlightsMode currentHeadlightsMode;
extern bool sireneEnabled;
extern bool flashLeft;
extern bool flashRight;
extern bool glowBrake;
extern bool glowReverse;
