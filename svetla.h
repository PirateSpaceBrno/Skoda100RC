enum headlightsMode {
  VYPNUTO,
  OBRYSOVA,
  POTKAVACI,
  DALKOVA
};

void controlBlinkLights(bool left, bool right);
void controlLights(headlightsMode mode);
void setupLights();
