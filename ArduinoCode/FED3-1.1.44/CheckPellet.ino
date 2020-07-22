/********************************************************
  Check if food is available.  If so return true.
********************************************************/
bool CheckForPellet () {
  if (FEDmode != 5) {  // if not an extinction session
    if (FEDmode == 6 && Ratio_Met == false && PelletAvailable == false) {  // if light tracking session, display light tracking stimulus
      if (activePoke == 1) leftStimulus() ;
      if (activePoke == 0) rightStimulus() ;
    }

    if (digitalRead(PELLET_WELL) == HIGH && OutReady == true) {
      //      delay (300);
      //      if (digitalRead(PELLET_WELL) == HIGH ) {  //if pellet is out for 300ms
      OutReady = false;
      if (PelletCount > 0) {  // This skips logging for the first trial if the FED starts with a pellet in the well
        pellet = true;
        Blink(BNC_OUT, 200, 1); //one pulse for pellet retrieval
        //get time of pellet removal in unixtime seconds since 1970, and subtract pelletTime to determine how long the pellet was in the well
        DateTime now = rtc.now();
        retInterval = now.unixtime() - pelletTime;
        DisplayRetrievalInt();
        logdata();
      }

      Timeout();

      /********************************************************
        Light tracking task
      ********************************************************/
      if (FEDmode == 6) activePoke = random (0, 2); // randomize Active poke in light tracking task
      UpdateDisplay();
      //      }
    }

    PelletAvailable = false;
    if (digitalRead(PELLET_WELL) == LOW ) {
      //get time of pellet drop in unixtime seconds since 1970
      DateTime now = rtc.now();
      pelletTime = now.unixtime();
      PelletAvailable = true;
      if (CountReady == true) {
        PelletCount++;
        CountReady = false;
        OutReady = true;
        TimeoutReady = true;
        Ratio_Met = false;

        /********************************************************
          Progressive Ratio
        ********************************************************/
        ratio = ratio + round ((5 * exp (0.2 * PelletCount)) - 5); // this is a formula from Richardson and Roberts (1996) https://www.ncbi.nlm.nih.gov/pubmed/8794935
      }

    }

  }

  else {  // if it is an extinction session, trick FED into thinking a pellet was dispensed
    PelletAvailable = true;
    OutReady = true;
    TimeoutReady = true;
    Ratio_Met = false;
    UpdateDisplay();
  }
}
