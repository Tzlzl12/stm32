#include <iwdg.h>

void IWDG_Config()
{
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  IWDG_SetPrescaler(IWDG_Prescaler_64);
  IWDG_SetReload(625);

  IWDG_ReloadCounter();

  IWDG_Enable();
}
