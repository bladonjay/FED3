/********************************************************
  Conditioned stimlus
********************************************************/
void ConditionedStimulus() {
  tone (BUZZER, 4000, 300);
  colorWipe(strip.Color(0, 2, 2), 40); // Color wipe
  colorWipe(strip.Color(0, 0, 0), 20); // OFF
}

void RConditionedStim() {
  tone (BUZZER, 4000, 300);
  RcolorWipe(strip.Color(0, 2, 2), 40); // Color wipe
  RcolorWipe(strip.Color(0, 0, 0), 20); // OFF
}

/********************************************************
  Visual tracking stimulus - left
********************************************************/
void leftStimulus() {
  strip.setPixelColor(0, strip.Color(2, 0, 2, 2) );
  strip.show();
}


/********************************************************
  Visual tracking stimulus - right
********************************************************/
void rightStimulus() {
  strip.setPixelColor(7, strip.Color(2, 0, 2, 2) );
  strip.show();
}
