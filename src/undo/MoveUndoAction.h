/*
 * Xournal++
 *
 * Undo move action (EditSelection)
 *
 * @author Xournal Team
 * http://xournal.sf.net
 *
 * @license GPL
 */

#ifndef __MOVEUNDOACTION_H__
#define __MOVEUNDOACTION_H__

#include "UndoAction.h"
#include <glib.h>

class EditSelection;
class VerticalToolHandler;
class XojPage;
class Layer;
class Redrawable;

class MoveUndoAction: public UndoAction {
public:
	MoveUndoAction(Layer * sourceLayer, XojPage * sourcePage, Redrawable * sourceView, GList * selected, double mx, double my, Layer * targetLayer, XojPage * targetPage, Redrawable * targetView);
	MoveUndoAction(XojPage * sourcePage, VerticalToolHandler * handler);
	virtual ~MoveUndoAction();

public:
	void finalize(VerticalToolHandler * handler);

	virtual bool undo(Control * control);
	virtual bool redo(Control * control);
	XojPage ** getPages();
	virtual String getText();

private:
	void acceptPositions(GList * pos);
	void switchLayer(GList * entries, Layer * oldLayer, Layer * newLayer);
	void repaint(Redrawable * view, GList * list, GList * list2 = NULL);
	void repaint();

private:
	XOJ_TYPE_ATTRIB;

	GList * sourcePos;
	GList * targetPos;
	XojPage * targetPage;

	Layer * sourceLayer;
	Layer * targetLayer;

	Redrawable * sourceView;
	Redrawable * targetView;

	String text;

	friend class EditSelection;
};

#endif /* __MOVEUNDOACTION_H__ */