
class CTwixSplitter : public CSplitterWnd
{
	BOOL SplitRow(int cyBefore);
	BOOL SplitColumn(int cxBefore);
	void DeleteView(int row, int col);
public:
	void SplitRow();
	void SplitColumn();
};
