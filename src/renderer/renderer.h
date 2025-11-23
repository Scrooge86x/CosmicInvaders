#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "model.h"
#include "shader.h"

template<typename Derived>
class Renderer {
public:
	void beginFrame() {
		static_cast<Derived*>(this)->beginFrameImpl();
	}

	void endFrame() {
		static_cast<Derived*>(this)->endFrameImpl();
	}

	void submit() {
		static_cast<Derived*>(this)->submitImpl();
	}
	void flush() {
		static_cast<Derived*>(this)->flushImpl();
	}

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;

private:
	friend Derived;
	Renderer() {};
};

#endif 