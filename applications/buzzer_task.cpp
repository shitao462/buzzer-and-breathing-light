#include "cmsis_os.h"
#include "io/buzzer/buzzer.hpp"

namespace
{
constexpr float kBuzzerTimerClockHz = 84e6f;
constexpr float kBeepFrequencyHz = 5000.0f;
constexpr float kBeepDutyCycle = 0.1f;
constexpr uint32_t kBeepDurationMs = 100;
constexpr uint32_t kBeepIntervalMs = 100;
constexpr uint8_t kBeepCount = 3;

sp::Buzzer buzzer(&htim4, TIM_CHANNEL_3, kBuzzerTimerClockHz);
}  // namespace

extern "C" void buzzer_task(void const * argument)
{
  (void)argument;
  buzzer.set(kBeepFrequencyHz, kBeepDutyCycle);

  for (uint8_t i = 0; i < kBeepCount; ++i) {
    buzzer.start();
    osDelay(kBeepDurationMs);
    buzzer.stop();

    if (i + 1 < kBeepCount) {
      osDelay(kBeepIntervalMs);
    }
  }

  // 启动提示音只播放一次；保留任务，避免任务函数返回。
  while (true) {
    osDelay(1000);
  }
}
