#include "ScaleUndoAction.h"

#include "../model/Page.h"
#include "../model/Element.h"
#include "../util/Range.h"
#include "../gui/Redrawable.h"

ScaleUndoAction::ScaleUndoAction(XojPage * page, Redrawable * view, GList * elements, double x0, double y0, double fx, double fy) {
	XOJ_INIT_TYPE(ScaleUndoAction);

	this->page = page;
	this->view = view;
	this->elements = g_list_copy(elements);
	this->page->reference(19);
	this->x0 = x0;
	this->y0 = y0;
	this->fx = fx;
	this->fy = fy;
}

ScaleUndoAction::~ScaleUndoAction() {
	XOJ_CHECK_TYPE(ScaleUndoAction);

	this->page->unreference(20);
	this->page = NULL;
	this->view = NULL;
	g_list_free(this->elements);
	this->elements = NULL;

	XOJ_RELEASE_TYPE(ScaleUndoAction);
}

bool ScaleUndoAction::undo(Control * control) {
	XOJ_CHECK_TYPE(ScaleUndoAction);

	applayScale(1 / this->fx, 1 / this->fy);
	this->undone = true;
	return true;
}

bool ScaleUndoAction::redo(Control * control) {
	XOJ_CHECK_TYPE(ScaleUndoAction);

	applayScale(this->fx, this->fy);
	this->undone = false;
	return true;
}

void ScaleUndoAction::applayScale(double fx, double fy) {
	XOJ_CHECK_TYPE(ScaleUndoAction);

	if (this->elements == NULL) {
		return;
	}

	Element * first = (Element *) elements->data;
	Range r(first->getX(), first->getY());

	for (GList * l = this->elements; l != NULL; l = l->next) {
		Element * e = (Element *) l->data;
		r.addPoint(e->getX(), e->getY());
		r.addPoint(e->getX() + e->getElementWidth(), e->getY() + e->getElementHeight());
		e->scale(this->x0, this->y0, fx, fy);
		r.addPoint(e->getX(), e->getY());
		r.addPoint(e->getX() + e->getElementWidth(), e->getY() + e->getElementHeight());
	}

	this->view->rerenderRange(r);
}

String ScaleUndoAction::getText() {
	XOJ_CHECK_TYPE(ScaleUndoAction);

	return _("Scale");
}