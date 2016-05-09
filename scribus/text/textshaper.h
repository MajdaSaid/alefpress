#ifndef TEXTSHAPER_H
#define TEXTSHAPER_H

#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>

#include <unicode/uscript.h>
#include "itextsource.h"
#include "itextcontext.h"

class GlyphCluster;
class StoryText;
class PageItem;

class TextShaper
{
public:
	TextShaper(ITextContext* context, ITextSource& story, int first, bool singlePar=false);
	TextShaper(ITextSource &story, int first);

	QList<GlyphCluster> shape();

private:
	struct TextRun {
		TextRun(int s, int l, int d)
			: start(s), len(l), dir(d), script(USCRIPT_INVALID_CODE)
		{ }

		TextRun(int s, int l, int d, UScriptCode sc)
			: start(s), len(l), dir(d), script(sc)
		{ }

		int start;
		int len;
		int dir;
		UScriptCode script;
	};

	struct FeaturesRun {
		FeaturesRun(int s, int l, QStringList f)
			: start(s), len(l), features(f)
		{
		}

		int start;
		int len;
		QStringList features;
	};

	void buildText(QString &text, QMap<int, int> &textMap);
	QList<TextRun> itemizeBiDi(const QString &text);
	QList<FeaturesRun> itemizeFeatures(const TextRun &runs);
	QList<TextRun> itemizeScripts(const QString &text, const QList<TextRun> &runs);
	QList<TextRun> itemizeStyles(const QMap<int, int> &textMap, const QList<TextRun> &runs);

	ITextContext* m_context;
	ITextSource& m_story;
	int m_firstChar;
	bool m_singlePar;
	QString m_text;
	QMap<int, int> m_textMap;
};

#endif // TEXTSHAPER_H
