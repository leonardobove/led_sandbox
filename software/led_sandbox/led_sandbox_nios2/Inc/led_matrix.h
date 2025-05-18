#ifndef INC_LED_MATRIX_H_
#define INC_LED_MATRIX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "system.h"
#include "io.h"
#include <stdint.h>
#include <stdio.h>
#include "altera_up_avalon_video_dma_controller.h"


//DMA DEFINITIONS
#define DMA_EN_OFFSET            (0u)
#define DMA_START_OFFSET         (3u)
#define DMA_ENABLE_BIT           ((1u) << 2)

extern alt_up_video_dma_dev* dev;
void swap_lines (uint8_t *temp_buf);

// LED_MATRIX_DRIVER DEFINITIONS

#define RESET_OFFSET              (0u)
#define ENABLE_OFFSET             (1u)
#define MATRIX_ENABLE             (1u)
#define MATRIX_DISABLE            (0u)
#define MATRIX_RESET              (1u)

#define LED_MATRIX_DRIVER_RESET   (IOWR(LED_MATRIX_DRIVER_0_BASE, RESET_OFFSET,  MATRIX_RESET))
#define LED_MATRIX_DRIVER_ENABLE  (IOWR(LED_MATRIX_DRIVER_0_BASE, ENABLE_OFFSET, MATRIX_ENABLE))
#define LED_MATRIX_DRIVER_DISABLE (IOWR(LED_MATRIX_DRIVER_0_BASE, ENABLE_OFFSET, MATRIX_DISABLE))

#ifdef __cplusplus
}
#endif

#endif /* INC_LED_MATRIX_H_ */
