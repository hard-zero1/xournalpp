/*
 * Xournal++
 *
 * [Header description]
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include <string>
#include <vector>

#include "PenInputHandler.h"
#include "XournalType.h"

class InputContext;

class StylusInputHandler: public PenInputHandler {
public:
    explicit StylusInputHandler(InputContext* inputContext);
    ~StylusInputHandler();

    bool handleImpl(InputEvent const& event) override;
    bool changeTool(InputEvent const& event) override;

private:
    /**
     * How many events since hitting the screen with the pen should be ignored before actually starting the action.
     * >0: Ignore the "nrOfIgnoredEvents" first events
     * =0: The next event will start the action
     * -1: Action already started
     * (Explanation: When the pen is pressed on the screen, the accuracy and update rate of its recognized position increases. Because of the lower precision before, when hitting the screen the cursor position might jump from its previous position to the more precise point (this is especially far, if the pen tip was in rapid movement right before touching) while beeing recognized as writing. This can result in artifacts that e.g. make handwritten text very hard to read. To work around this, the first events since the triggering event can be ignored)
     */
    int nrOfIgnoredEvents = 0;

private:
    void setPressedState(InputEvent const& event);
};
