/* bzflag
 * Copyright (c) 1993 - 2009 Tim Riker
 *
 * This package is free software;  you can redistribute it and/or
 * modify it under the terms of the license found in the file
 * named COPYING that should have accompanied this file.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef	BZF_CONTROL_PANEL_H
#define	BZF_CONTROL_PANEL_H

#if defined(_MSC_VER)
  #pragma warning(disable: 4786)
#endif

// common - 1st
#include "common.h"

// system headers
#include <string>
#include <vector>
#include <deque>
#include <map>

//common headers
#include "bzfgl.h"
#include "vectors.h"

// local headers
#include "MainWindow.h"

class RadarRenderer;
class SceneRenderer;
class LocalFontFace;


struct ControlPanelMessage {
  ControlPanelMessage(const std::string&);
  void breakLines(float maxLength, int fontFace, float fontSize);

  std::string string;
  std::vector<std::string> lines;
  int numlines;
};


class ControlPanel {
  public:
    enum MessageModes {
      MessageAllTabs = -2,
      MessageCurrent = -1,
      MessageAll     = 0,
      MessageChat    = 1,
      MessageServer  = 2,
      MessageMisc    = 3,
      MessageDebug   = 4,
      MessageModeCount
    };

    typedef std::deque<ControlPanelMessage> MessageQueue;
    typedef std::map<std::string, int>      TabMap;

  public:
    ControlPanel(MainWindow&, SceneRenderer&);
    ~ControlPanel();

    void setControlColor(const fvec4* color = NULL);
    void render(SceneRenderer&);
    void resize();
    void invalidate();

    void setNumberOfFrameBuffers(int);

    bool addTab(const std::string& label, bool allSrc, bool allDst);
    bool removeTab(const std::string& label);
    bool renameTab(const std::string& oldLabel,
                   const std::string& newLabel);

    void addMessage(const std::string&, int tabMode = MessageMisc);
    void addMessage(const std::string&, const std::string& tabLabel);

    void setMessagesOffset(int offset, int whence, bool paged);

    bool setActiveTab(int tabID);
    int  getActiveTab() const { return activeTab; }

    bool clearTab(int tabID);
    bool shiftTab(int tabID, int distance);

    bool isTabLocked(int tabID) const;
    bool isTabVisible(int tabID) const;

    int                getTabCount() const { return (int)tabs.size(); }
    int                getTabID(const std::string& label) const;
    const std::string& getTabLabel(int tabID) const;

    int                getCurrentTabID()    const;
    const std::string& getCurrentTabLabel() const;

    void setRadarRenderer(RadarRenderer*);

    void setDimming(float dimming);

    bool saveMessages(const std::string& filename, bool stripAnsi,
                      const std::string& tabLabel = "All") const;

    int getTabMessageCount(int tabID);
    const MessageQueue* getTabMessages(int tabID);
    const MessageQueue* getTabMessages(const std::string& tabLabel);

  private:
    // no copying!
    ControlPanel(const ControlPanel&);
    ControlPanel& operator=(const ControlPanel&);

    static void resizeCallback(void*);
    static void exposeCallback(void*);
    static void bzdbCallback(const std::string& name, void* data);
    static void loggingCallback(int level, const std::string& msg, void* data);

    inline bool validTab(int tab) const {
      return (tab >= 0) && (tab < (int)tabs.size());
    }

  private:
    void setupTabMap();

    void drawTabBoxes(int yOffset);
    void drawTabLabels(int yOffset);
    void drawOutline(int yOffset);
    void drawScrollBar();

  private:
    struct IntRect {
      int xpos,  ypos;
      int xsize, ysize;
    };

    struct Tab {
      Tab(const std::string& l, bool lk, bool _allSrc, bool _allDst)
      : label(l)
      , locked(lk)
      , visible(true)
      , width(0.0f)
      , allSrc(_allSrc)
      , allDst(_allDst)
      , unread(false)
      , offset(0)
      , msgCount(0)
      {}
      std::string label;
      bool  locked;   // can not be removed
      bool  visible;
      float width;
      bool  allSrc;   // feeds into the 'All' tab
      bool  allDst;   // receives MessageAllTabs messages
      bool  unread;   // has unread messages
      int   offset;   // for scrolling
      int   msgCount; // tally of all messages
      MessageQueue messages;
    };
    std::vector<Tab*> tabs;

    TabMap tabMap;

    int	activeTab;

    bool tabsOnRight;
    long totalTabWidth;

    MainWindow&		window;
    bool		resized;
    int			numBuffers;
    int			exposed;
    int			changedMessage;
    RadarRenderer*	radarRenderer;
    SceneRenderer*	renderer;

    LocalFontFace*	fontFace;
    float		fontSize;

    float		dimming;
    float		du, dv;
    IntRect		radarRect;
    IntRect		messageRect;
    fvec4		teamColor;
    int			maxLines;
    float		margin;
    float		lineHeight;

    static const int	maxScrollPages;
};


inline void ControlPanel::setDimming(float newDimming)
{
  const float newDim = 1.0f - newDimming;
  dimming = (newDim > 1.0f) ? 1.0f : (newDim < 0.0f) ? 0.0f : newDim;
}


#endif // BZF_CONTROL_PANEL_H

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
