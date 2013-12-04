/*
 * Copyright 2013  Giulio Camuffo <giuliocamuffo@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "layer.h"
#include "transform.h"
#include "shellsignal.h"

struct weston_view;

class Shell;

class Workspace {
public:
    Workspace(Shell *shell, int number);
    ~Workspace();

    void init(wl_client *client);
    void createBackgroundView(weston_surface *bkg);

    void addSurface(ShellSurface *surface);
    void restack(ShellSurface *surface);
    void stackAbove(weston_view *surf, weston_view *parent);

    void setTransform(const Transform &tr);

    inline int number() const { return m_number; }
    int numberOfSurfaces() const;
    struct weston_output *output() const;
    wl_resource *resource() const { return m_resource; }

    void insert(Workspace *ws);
    void insert(Layer *layer);
    void insert(struct weston_layer *layer);
    void remove();

    void setActive(bool active);
    bool active() const { return m_active; }

    inline const Layer &layer() const { return m_layer; }

    static Workspace *fromResource(wl_resource *res);

    Signal<Workspace *> destroyedSignal;

private:
    void removed(wl_client *client, wl_resource *res);

    Shell *m_shell;
    int m_number;
    wl_resource *m_resource;
    weston_view *m_rootSurface;
    weston_view *m_background;
    Transform m_transform;
    Layer m_backgroundLayer;
    Layer m_layer;
    bool m_active;

    static const struct desktop_shell_workspace_interface s_implementation;
};

#endif
