#pragma once
#include "clutil.h"
#include <float.h>
#include <stdlib.h>
#include "common/mat.h"
#include "transforms/transform.h"
#include "transforms/loadyuv.h"

const bool send_raw_pred = getenv("SEND_RAW_PRED") != NULL;

void softmax(const float* input, float* output, size_t len);
float softplus(float input);
float sigmoid(float input);

typedef struct ModelFrame {
  Transform transform;
  int transformed_width, transformed_height;
  cl_mem transformed_y_cl, transformed_u_cl, transformed_v_cl;
  LoadYUVState loadyuv;
  cl_mem net_input;
  size_t net_input_size;
} ModelFrame;

void frame_init(ModelFrame* frame, CLContext *ctx, int width, int height);
float *frame_prepare(ModelFrame* frame, cl_command_queue q,
                           cl_mem yuv_cl, int width, int height,
                           const mat3 &transform);
void frame_free(ModelFrame* frame);
