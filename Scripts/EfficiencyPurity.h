#ifndef EFFICIENCYPURITY_H
#define EFFICIENCYPURITY_H

// cpp
#include <bitset>
#include <vector>
#include <string>
#include <iostream>

// local
#include "DataTypes.h"

namespace numusel{

  class EfficiencyPurity{

    public:

      void FillEfficiencyDenominator(eff_1d* eff_plots, std::vector<double> vals, std::bitset<8> evcat, var_list* vars);

      void FillEfficiencyNumerator(eff_1d* eff_plots, std::vector<double> vals, std::bitset<8> evcat, var_list* vars);

      void FillPurityDenominator(pur_1d* pur_plots, std::vector<double> vals, std::bitset<8> evcat, var_list* vars);
 
      void FillPurityNumerator(pur_1d* pur_plots, std::vector<double> vals, std::bitset<8> evcat, var_list* vars);

  };

}

#endif