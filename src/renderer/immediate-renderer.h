#pragma once

#ifndef IMMEDIATE_RENDERER_H
#define IMMEDIATE_RENDERER_H

#include "renderer.h"

class ImmediateRenderer : public Renderer<ImmediateRenderer> {
public:
	static ImmediateRenderer& getInstance() {
		static ImmediateRenderer instance;
		return instance;
	}

	ImmediateRenderer(const ImmediateRenderer&) = delete;
	ImmediateRenderer& operator=(const ImmediateRenderer&) = delete;

	ImmediateRenderer(ImmediateRenderer&&) = delete;
	ImmediateRenderer& operator=(ImmediateRenderer&&) = delete;

	ImmediateRenderer();

	~ImmediateRenderer() = default;

	void beginFrame();
	void endFrame();
	void submit();
	void flush();

private:
	friend Renderer<ImmediateRenderer>;
};

#endif