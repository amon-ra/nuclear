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

#ifndef DESKTOP_SHELL_H
#define DESKTOP_SHELL_H

#include <list>

#include "shell.h"
#include "utils.h"

class InputPanel;
class WlShell;
class XWlShell;

class DesktopShell : public Shell {
public:
    DesktopShell(struct weston_compositor *ec);
    ~DesktopShell();

protected:
    virtual void init();
    virtual void setGrabCursor(uint32_t);
    virtual void panelConfigure(weston_surface *es, int32_t sx, int32_t sy, Shell::PanelPosition pos) override;

private:
    void sendInitEvents();
    void workspaceAdded(Workspace *ws);
    void surfaceResponsivenessChanged(ShellSurface *shsurf, bool responsive);
    void bind(struct wl_client *client, uint32_t version, uint32_t id);
    void unbind(struct wl_resource *resource);
    void moveBinding(struct weston_seat *seat, uint32_t time, uint32_t button);
    void resizeBinding(struct weston_seat *seat, uint32_t time, uint32_t button);
    void setBusyCursor(ShellSurface *shsurf, weston_seat *seat);
    void endBusyCursor(weston_seat *seat);

    void setBackground(struct wl_client *client, struct wl_resource *resource, struct wl_resource *output_resource,
                                             struct wl_resource *surface_resource);
    void setPanel(wl_client *client, wl_resource *resource, uint32_t id, wl_resource *output_resource, wl_resource *surface_resource, uint32_t position);
    void setLockSurface(struct wl_client *client, struct wl_resource *resource, struct wl_resource *surface_resource);
    void setPopup(wl_client *client, wl_resource *resource, uint32_t id, wl_resource *parent_resource, wl_resource *surface_resource, int x, int y);
    void unlock(struct wl_client *client, struct wl_resource *resource);
    void setGrabSurface(struct wl_client *client, struct wl_resource *resource, struct wl_resource *surface_resource);
    void desktopReady(struct wl_client *client, struct wl_resource *resource);
    void addKeyBinding(struct wl_client *client, struct wl_resource *resource, uint32_t id, uint32_t key, uint32_t modifiers);
    void addOverlay(struct wl_client *client, struct wl_resource *resource, struct wl_resource *output_resource, struct wl_resource *surface_resource);
    void createGrab(wl_client *client, wl_resource *resource, uint32_t id);
    void addWorkspace(wl_client *client, wl_resource *resource);
    void selectWorkspace(wl_client *client, wl_resource *resource, wl_resource *workspace_resource);
    void quit(wl_client *client, wl_resource *resource);

    static void configurePopup(weston_surface *es, int32_t sx, int32_t sy);

    static const struct desktop_shell_interface m_desktop_shell_implementation;

    struct Output {
        weston_output *output;
        wl_resource *resource;
        IRect2D rect;
    };
    std::list<Output> m_outputs;
    InputPanel *m_inputPanel;
};

#endif
